#include <stdio.h>
#include <string>
#include <iostream>
#include <functional>
#include <exception>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <experimental/filesystem>

const bool kPrintTaskFile = false;
const bool kPrintDebugStatements = false;
const bool kDoNotPrintForPascal = false;
const std::string kCacheFilename = "cache.csv";

std::map<std::string, std::string> compilation_commands({
   { "c++", "g++ -O2 -DCONTEST -s -static -lm -w" },
   { "c", "gcc -std=c99 -O2 -DCONTEST -s -static -lm -w" },
   { "pas", "fpc -O2 -dCONTEST -XS" },
   { "java", "javac" }
});

struct TopLevel {
   /* Attribute name -> attribute type */
   const std::map<std::string, std::string> attributes;
   
   TopLevel(const std::map<std::string, std::string>& attributes) : 
      attributes(attributes) { }
   TopLevel() { } 
};

class ParsingException : public std::logic_error {
public:
   
   ParsingException(const std::string& msg) : std::logic_error("Parsing Error:    " + msg) {
      std::cout << what() << std::endl; 
   }

};

class GeneratingException : public std::logic_error {
public:

   GeneratingException(const std::string& msg) : std::logic_error("Generating Error: " + msg) {
      std::cout << what() << std::endl; 
   }
};

class AbstractTopLevel {
public:
   // TODO: maybe check that each field is only set once.
   virtual void setStringAttribute(const std::string& attr_name, const std::string& value) { };
   virtual void setCountAttribute(const std::string& attr_name, size_t value) { };
   virtual void setDoubleAttribute(const std::string& attr_name, double value) { };
   virtual void setListCountAttribute(const std::string& attr_name, std::vector<size_t> value) { };
   virtual void setTopLevelAttribute(const std::string& attr_name, AbstractTopLevel * topLevel) { };
   virtual void setListTopLevelAttribute(const std::string& attr_name, std::vector<AbstractTopLevel*> topLevel) { };
   virtual void setFlagAttribute(const std::string& attr_name) { };
};

/* Details for the person who wrote a solution. */
class Person : public AbstractTopLevel {
public:
   std::string name;
   std::string school;

   void setStringAttribute(const std::string& attr_name, const std::string& value) override {
      if (attr_name == "name") name = value;
     else if (attr_name == "school") school = value;
   }
};

/* Details for a single solution. */
class Solution : public AbstractTopLevel {
public:
   std::string name;
   std::string source;
   std::string lang;
   std::string comment;
   double special_time_limit = 0.0;
   
   size_t passes_up_to; // TODO: maybe set to default value.
   bool passes_all = false;
   std::vector<size_t> passes_all_except_for;
   std::vector<size_t> passes_only;
   
   Person * author;
   
   void setListCountAttribute(const std::string& attr_name, std::vector<size_t> value) override {
      if (attr_name == "passes_all_except_for") passes_all_except_for = value;
      else if (attr_name == "passes_only") passes_only = value;
   }
   
   void setStringAttribute(const std::string& attr_name, const std::string& value) override {
      if (attr_name == "name") name = value;
      else if (attr_name == "source") source = value;
      else if (attr_name == "lang") lang = value;
      else if (attr_name == "comment") comment = value;
   }
   
   void setCountAttribute(const std::string& attr_name, size_t value) override {
      if (attr_name == "passes_up_to") passes_up_to = value;
   }
   
   void setDoubleAttribute(const std::string& attr_name, double value) override {
      if (attr_name == "special_time_limit") special_time_limit = value;
   }
   
   void setFlagAttribute(const std::string& attr_name) override {
      if (attr_name == "passes_all") passes_all = true;
   }
   
   void setTopLevelAttribute(const std::string& attr_name, AbstractTopLevel * topLevel) {
      if (attr_name == "author") author = (Person *) topLevel;
   }
   
   ~Solution() {
      delete author;
   }
};

/* Details for a task. */
class Task : public AbstractTopLevel {
public:
   std::string name;
   std::string files_dir;
   size_t test_count;
   std::vector<size_t> weights;
   std::vector<Solution*> solutions;
   std::string input_file;
   std::string output_file;
   double time_limit;
   size_t mem_limit = 0;
   
   // Automatically populated by the tool.
   std::string source_directory;
   size_t contest;
   
   void setStringAttribute(const std::string& attr_name, const std::string& value) override {
      if (attr_name == "name") name = value;
      else if (attr_name == "files_dir") files_dir = value;
      else if (attr_name == "input_file") input_file = value;
      else if (attr_name == "output_file") output_file = value;
   }
   
   void setCountAttribute(const std::string& attr_name, size_t value) override {
      if (attr_name == "test_count") test_count = value;
      else if (attr_name == "mem_limit") mem_limit = value;
   }
   
   void setDoubleAttribute(const std::string& attr_name, double value) override {
      if (attr_name == "time_limit") time_limit = value;
   }
   
   void setListCountAttribute(const std::string& attr_name, std::vector<size_t> value) override {
      if (attr_name == "weights") weights = value;
   }
   
   void setListTopLevelAttribute(const std::string& attr_name, std::vector<AbstractTopLevel*> topLevel) {
      if (attr_name == "solutions") {
         for (AbstractTopLevel* item : topLevel) {
            solutions.push_back((Solution*) item);
         }
      }
   }
   ~Task() {
      for (Solution * solution : solutions) {
         delete solution;
     }       
   }
};

std::string LIST_TYPE = "list_";
std::string TOP_LEVEL_TYPE = "top_";
std::string STRING_TYPE = "string";
std::string PATH_TYPE = "path";
std::string COUNT_TYPE = "count";
std::string FLAG_TYPE = "flag";
std::string DOUBLE_TYPE = "double";

// Derived types.
std::string LIST_COUNT = LIST_TYPE + COUNT_TYPE;
std::string WEIGHTS_TYPE = LIST_TYPE + COUNT_TYPE;
std::string SOLUTIONS_TYPE = LIST_TYPE + TOP_LEVEL_TYPE + "SOLUTION";
std::string PERSON_TYPE = TOP_LEVEL_TYPE + "PERSON";

TopLevel task_top_level({
   { "name", STRING_TYPE },
   { "files_dir", PATH_TYPE },
   { "test_count", COUNT_TYPE },
   { "weights", WEIGHTS_TYPE },
   { "solutions", SOLUTIONS_TYPE },
   { "input_file", STRING_TYPE },
   { "output_file", STRING_TYPE },
   { "time_limit", DOUBLE_TYPE },
   { "mem_limit", COUNT_TYPE },
});

TopLevel solution_top_level({
   { "name", STRING_TYPE },
   { "source", STRING_TYPE },
   { "passes_up_to", COUNT_TYPE },
   { "passes_all", FLAG_TYPE },
   { "passes_all_except_for", LIST_COUNT },
   { "passes_only", LIST_COUNT },
   { "lang", STRING_TYPE },
   { "author", PERSON_TYPE },
   { "comment", STRING_TYPE },
   { "special_time_limit", DOUBLE_TYPE },
});

TopLevel person_top_level({
   { "name", STRING_TYPE },
   { "school", STRING_TYPE },
});

std::map<std::string, TopLevel> top_level_registry({
   { "TASK", task_top_level },
   { "SOLUTION", solution_top_level },
   { "PERSON", person_top_level }
});

std::map<std::string, std::function<AbstractTopLevel*(void)>> factories({
   { "TASK", []() { return new Task(); } },
   { "SOLUTION", []() { return new Solution(); } },
   { "PERSON", []() { return new Person(); } }
});

struct FileReader {
   
   std::string text;
   const std::string filename;
   size_t location = 0;
   
   FileReader(const std::string& filename) : filename(filename) {
      std::ifstream t(filename);
      if (!t) {
         throw ParsingException("File does not exist: " + filename);
      }
      std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
      text = str;
     t.close();
     if (kPrintDebugStatements) {
         std::cout << "Text read : " << text << std::endl;
     }
   }
   
   char current() { return text[location]; }
   void advance() { ++location; }
   
   void processExactString(const std::string& str) {
      size_t idx = 0;
      while (idx < str.size() && location < text.size() && str[idx] == current()) {
         ++idx;
         advance();
      }
      if (idx != str.size()) {
       throw ParsingException("Could not parse exact string: " + str);
      }
   }
   
   void readExactChar(char c) {
      if (current() != c) {
         throw ParsingException(filename + ": Found " + std::string(1, current()) + " instead of " + std::string(1, c) + ".");
      }
      advance();
   }
   
   bool isLetter(char c) { return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'); }
   bool isSymbol(char c) { return (c == '"' || c == ',' || c == '(' || c == ')' || c == '=' || c == '[' || c == ']'); }
   bool isNumeric(char c) { return '0' <= c && c <= '9'; }
   bool isAttributeChar(char c) { return isLetter(c) || c == '_'; }
   
   bool isMeaningful(char c) {
      return isLetter(c) || isSymbol(c) || isNumeric(c);
   }
   
   void readToMeaningful() {
      while (location < text.size() && !isMeaningful(current())) advance();
   }
   
   std::string readAttributeName() {
      std::string cur = "";
      while (location < text.size() && isAttributeChar(current())) {
         cur += current();
         advance();
      }
      return cur;
   }
   
   std::string readStringUntil(char terminal) {
      std::string cur = "";
      while (location < text.size() && current() != terminal) {
         cur += current();
         advance();
      }
      return cur;
   }
   
   size_t readCount() {
      size_t count = 0;
      while (location < text.size() && isNumeric(current())) {
         count = count * 10 + (current() - '0');
         advance();
      }
      return count;
   }
   
   double readDouble() {
      try{
         size_t double_char_length = 0;
         double value = std::stod(&text[location], &double_char_length);
         location += double_char_length;
         return value;
      } catch (...) {
         throw ParsingException(filename + ": Could not parse double.");
      }
   }
   
   bool isListType(const std::string& type) {
      return type.substr(0, LIST_TYPE.length()) == LIST_TYPE;
   }
   
   bool isTopLevelType(const std::string& type) {
      return type.substr(0, TOP_LEVEL_TYPE.length()) == TOP_LEVEL_TYPE;
   }
   
   std::string getInnerType(const std::string& type) {
      return type.substr(LIST_TYPE.length());
   }
   
   std::string getTopLevelInnerType(const std::string& type) {
      return type.substr(TOP_LEVEL_TYPE.length());
   }
   
   void processListAttribute(const std::string& name, const std::string& type, AbstractTopLevel* topLevel) {
      std::string innerType = getInnerType(type);
      readExactChar('[');
      readToMeaningful();
      // TODO: insert other types of lists. 
      if (innerType == COUNT_TYPE) {
         std::vector<size_t> values;
         while (true) {
            if (current() == ']') break;
            size_t value = readCount();
            values.push_back(value);
            readToMeaningful();
            if (current() == ']') break;
            readExactChar(',');
            readToMeaningful();
         }
         topLevel->setListCountAttribute(name, values);
      }
      else if (isTopLevelType(innerType)) {
         std::vector<AbstractTopLevel*> values;
         while (true) {
            if (current() == ']') break;
            AbstractTopLevel* value = processTopLevel(getTopLevelInnerType(innerType));
            values.push_back(value);
            readToMeaningful();
            if (current() == ']') break;
            readExactChar(',');
            readToMeaningful();
         }
         topLevel->setListTopLevelAttribute(name, values);
      } else {
         throw ParsingException("Unknown list type: " + innerType + ".\n");
      }
      readExactChar(']');
   }
         
   void processAttribute(const std::string& name, const std::string& type, AbstractTopLevel* topLevel) {
      if (type == STRING_TYPE) {
         readExactChar('"');
         std::string value = readStringUntil('"');
         readExactChar('"');
         topLevel->setStringAttribute(name, value);
      } else if (type == PATH_TYPE) {
         readExactChar('"');
         std::string value = readStringUntil('"');
         readExactChar('"');
         // TODO: maybe add checks for paths.
         topLevel->setStringAttribute(name, value);
      } else if (type == COUNT_TYPE) {
         size_t value = readCount();
         topLevel->setCountAttribute(name, value);
      } else if (type == DOUBLE_TYPE) {
         double value = readDouble();
         topLevel->setDoubleAttribute(name, value);
      } else if (isListType(type)) {
         processListAttribute(name, type, topLevel);
      } else if (isTopLevelType(type)) {
         AbstractTopLevel * value = processTopLevel(getTopLevelInnerType(type));
         topLevel->setTopLevelAttribute(name, value);
      } else if (type == FLAG_TYPE) {
         topLevel->setFlagAttribute(name);
     } else {
         throw ParsingException("Could not recognise type" + type + ".");
      }
   }
   
   void processAttributes(
         const std::string& top_level_name,
         AbstractTopLevel* topLevel
         ) {
     const std::map<std::string, std::string>& attributes = top_level_registry[top_level_name].attributes;
      readToMeaningful();
      while (true) {
         if (current() == ')') break;
         std::string attributeName = readAttributeName();
       if (kPrintDebugStatements) {
          printf("Reading attribute: %s\n", attributeName.c_str());
       }
         if (attributes.find(attributeName) == attributes.end()) {
            throw ParsingException("Could not find attribute named '" + attributeName + "' for top level '" + top_level_name + "'.\n");
         }
         std::string attributeType = attributes.find(attributeName)->second;
         readToMeaningful();
         if (attributeType != FLAG_TYPE) {
            readExactChar('=');
            readToMeaningful();
         }
         processAttribute(attributeName, attributeType, topLevel);
         readToMeaningful();
         if (current() == ')') break;
         readExactChar(',');
         readToMeaningful();
         if (kPrintDebugStatements) {
            std::cout << "Finished reading attribute: " << attributeName << std::endl;
         }
      }
   }
   
   AbstractTopLevel* processTopLevel(const std::string& name) {
      if (factories.find(name) == factories.end()) {
         throw ParsingException("Could not top level " + name + ".");
      }
      AbstractTopLevel* topLevel = (factories[name])();
      processExactString(name);
      readToMeaningful();
      readExactChar('(');
      processAttributes(name, topLevel);
      readExactChar(')');
      return topLevel;
   }
};

void printIndents(size_t indent) {
   for (int i = 0; i < indent * 3; ++i) {
      printf(" ");
   }
}

void printStringAttribute(const std::string& name, const std::string& value, size_t indent) {
   if (value.empty()) return;
   printIndents(indent);
   std::cout << name << "=" << value << std::endl;
}

void printCountAttribute(const std::string& name, size_t value, size_t indent) {
   if (value == 0) return;
   printIndents(indent);
   std::cout << name << "=" << value << std::endl;
}

void printFlagAttribute(const std::string& name, bool value, size_t indent) {
   if (!value) return;
   printIndents(indent);
   std::cout << name << "=" << value << std::endl;
}

void printListCount(const std::string& name, const std::vector<size_t>& list_count, size_t indent) {
   if (list_count.empty()) return;
   printIndents(indent);
   std::cout << name << "= [";
   for (const size_t& val : list_count) {
      printf("%lud ", val);
   }
   std::cout << "]\n";
}

void print(const Person* const person, size_t indent) {
   printf("PERSON(\n");
   
   printStringAttribute("name", person->name, indent + 1);
   printStringAttribute("school", person->school, indent + 1);
   
   printIndents(indent);
   printf(")");
}

void print(const Solution * const solution, size_t indent) {
   printIndents(indent);
   printf("SOLUTION(\n");
   
   printStringAttribute("name", solution->name, indent + 1);
   printStringAttribute("source", solution->source, indent + 1);
   printCountAttribute("passes_up_to", solution->passes_up_to, indent + 1);
   printFlagAttribute("passes_all", solution->passes_all, indent + 1);
   printStringAttribute("lang", solution->lang, indent + 1);
   
   printListCount("passes_all_except_for", solution->passes_all_except_for, indent + 1);
   printListCount("passes_only", solution->passes_only, indent + 1);
   if (solution->author != NULL) {
      printIndents(indent + 1);
      std::cout << "author=";
      print(solution->author, indent + 1);
      std::cout << "\n";
   }
   
   printIndents(indent);
   printf(")");
}

void print(const Task* const task, size_t indent = 0) {
   printIndents(indent);
   printf("TASK(\n");
   
   printStringAttribute("files_dir", task->files_dir, indent + 1);
   printStringAttribute("name", task->name, indent + 1);
   printCountAttribute("test_count", task->test_count, indent + 1);
   printStringAttribute("input_file", task->input_file, indent + 1);
   printStringAttribute("output_file", task->output_file, indent + 1);
   printCountAttribute("time_limit", task->time_limit, indent + 1);
   printCountAttribute("mem_limit", task->mem_limit, indent + 1);
   printListCount("weights", task->weights, indent + 1);
   printIndents(indent + 1);
   std::cout << "solutions= [" << std::endl;
   for (const Solution* const sol : task->solutions) {
      print(sol, indent + 2);
      std::cout << ",\n";
   }
   printIndents(indent + 1);
   std::cout << "]" << std::endl;
   printf(")\n");
}

std::string replaceString(std::string & str, const std::string & from, const std::string & to) {
   while(str.find(from) != std::string::npos)
      str.replace(str.find(from), from.length(), to);
   return str;
}

std::string getFile(const std::string& filename, int i) {
   std::string new_string = filename;
   replaceString(new_string, "$i", std::to_string(i));
   return new_string;
}

std::string getStandardFile(const std::string& filename) {
   std::string new_string = filename;
   replaceString(new_string, "$i", "");
   return new_string;
}

std::vector<std::string> findAllPathsInDir() {
   std::vector<std::string> ans;
   for (const auto & entry : std::experimental::filesystem::recursive_directory_iterator(".")) {
      if (entry.path().filename() == "TASK") {
         ans.push_back(entry.path().relative_path());
      }
   }
   return ans;
}

void writeToFile(const std::string& str, const std::string& filename) {
   std::ofstream fout(filename);
   fout << str << "\n";
   fout.close();
}

// Process: 
//  1. Find all TASK files.
//  2. Parse all TASK files into TASK nodes.
//  (3. Detect any obvious errors) e.g. skipped files, file tested twice, solutions have different name, passes_up_to < test_count, report missing fields (e.g. timelimit)
//  4. For each TASK node generate all testing commands.
//  5. Print the commands in a separate file.

// Maybe create a script for calling g++ this && ./a.out && ./test_script.sh

std::vector<Task*> getAllTaskNodes(const std::vector<std::string>& paths, bool create_cache) {
   std::vector<Task*> tasks;
   for (const auto& str : paths) {
      FileReader file(str);
      Task * task = (Task*) file.processTopLevel("TASK");
      task->source_directory = str.substr(0, str.find_last_of("/\\"));
      task->contest = std::stoi(str.substr(str.find_last_of("-") -2, 2));
      tasks.push_back(task);
      if (kPrintTaskFile) {
         std::cout << "SOURCE : " << task->source_directory << std::endl;
         print(task);
      }
   }
   if (create_cache) {
      std::ofstream cache_out(kCacheFilename);
      for (Task* task : tasks) {
         cache_out << task->name << "," << task->source_directory << std::endl;
      }
      cache_out.close();
   }
   return tasks;
}

std::vector<size_t> getAllExceptFor(const std::vector<size_t>& except, size_t test_count) {
   std::set<size_t> except_set;
   for (const auto& v: except) except_set.insert(v);
   std::vector<size_t> ans;
   for (size_t i = 1; i <= test_count; ++i) {
      if (except_set.find(i) == except_set.end()) ans.push_back(i);
   }
   return ans;
}

struct ScriptBuilder {
   
   std::string code;
   
   ScriptBuilder() : code("source ./utils/test_functions.sh\nsource ./utils/fetch_testdata.sh\n") { }
   
   void addPrintStatement(const std::string& message) {
      code += "echo \"" + message + "\"\n";
   }
   
   void addCommandToFetchTestdataIfNotThere(size_t contest, const std::string& codename) {
      code += "fetch_testdata '" + std::to_string(contest) + "' '" + codename + "'\n";
   }      
   
   void addSolutions(Task * task) {
      addCommandToFetchTestdataIfNotThere(task->contest, task->name);
      addPrintStatement("TASK : " + task->name);
      for (Solution * solution : task->solutions) {
         addPrintStatement("   SOLUTION : " + solution->name);
         addSolution(task, solution);
      }
   }
   
   void addSolution(Task * task, Solution * solution) {
      if (kDoNotPrintForPascal && solution->lang == "pas") {
          return;
       }        
      std::string raw_input = task->input_file;
      std::string template_input_file = task->files_dir + raw_input + '#';
      
      std::string raw_output = task->output_file;
      std::string template_output_file = task->files_dir + raw_output + '#';
      
      
      if (compilation_commands.find(solution->lang) == compilation_commands.end()) {
         throw GeneratingException("Unknown language for solution: " + solution->name + ".");
      }
      
      if (solution->passes_all) {
         code += "array=(`seq 1 " + std::to_string(task->test_count) + "`)\n";
      } else if (!solution->passes_only.empty()) {
         code += "array=(";
         for (const auto& v : solution->passes_only) {
            code += " " + std::to_string(v);
         }
         code += ")\n";
      } else if (solution->passes_up_to != 0) {
         code += "array=(`seq 1 " + std::to_string(solution->passes_up_to) + "`)\n";
      } else if (!solution->passes_all_except_for.empty()) {
         std::vector<size_t> passes = getAllExceptFor(solution->passes_all_except_for, task->test_count);
         code += "array=(";
         for (const auto& v : passes) {
            code += " " + std::to_string(v);
         }
         code += ")\n";
      }
      double time_limit = solution->special_time_limit == 0.0 ? task->time_limit : solution->special_time_limit;
      code += "run_test '" + 
         template_input_file + "' '" + 
         template_output_file + "' '" + 
         raw_input + "' '" + 
         raw_output + "' '" + 
         task->source_directory + "/' '" + 
         solution->source + "' " + 
         std::to_string(time_limit) + " " + 
         std::to_string(task->mem_limit) + " '" + 
         compilation_commands[solution->lang] + 
         "' \"${array[@]}\" \n";
   }
   
   std::string getCode() {
      return code;
   }
};

void generateFileForTasks(std::vector<Task*>& tasks) {
   ScriptBuilder builder;
   for (Task * task : tasks) {
      builder.addSolutions(task);
   }
   writeToFile(builder.getCode(), "generated_execution.sh");
}

void generateFileForTasksFilterByTaskName(std::vector<Task*>& tasks, const std::string& task_name) {
   bool found = false;
   ScriptBuilder builder;
   for (Task * task : tasks) {
      if (task->name == task_name) {
         found = true;
         builder.addSolutions(task);
      }
   }
   if (found == false) {
      std::cout << "Error: No task found with the name " << task_name << "." << std::endl;
   }
   writeToFile(builder.getCode(), "generated_execution.sh");
}

void generateFileForTasksFilterByTaskAndSolution(std::vector<Task*>& tasks, const std::string& task_name, const std::string& solution_name) {
   if (solution_name.empty()) {
      generateFileForTasksFilterByTaskName(tasks, task_name);
      return;
   }
   bool found_solution = false;
   bool found_task = false;
   ScriptBuilder builder;
   for (Task * task : tasks) {
      if (task->name == task_name) {
         found_task = true;
         for (Solution * solution : task->solutions) {
            if (solution->name == solution_name) {
               found_solution = true;
               builder.addPrintStatement("SOLUTION: " + solution_name);
               builder.addCommandToFetchTestdataIfNotThere(task->contest, task_name);
               builder.addSolution(task, solution);
            }
         }
      }
   }
   if (found_task == false) {
      std::cout << "Error: No task found with the name " << task_name << "." << std::endl;
   } else if (found_solution == false) {
      std::cout << "Error: No solution with name " << solution_name << " found for " << task_name << "." << std::endl; 
   }
   writeToFile(builder.getCode(), "generated_execution.sh");
}

/* Attempts to retrieve the entry task_name from the cache. Otherwise, reads all TASK files
   and creates cache. */
std::vector<Task*> getTasksFor(std::string& task_name) {
   // Read the cache to check if it is present.
   if (std::experimental::filesystem::exists(kCacheFilename)) {
      std::ifstream cache_in(kCacheFilename);
      std::string s;
      std::string path;
      while (std::getline(cache_in, s)) {
         auto pos = s.find(',');
         std::string task = s.substr(0, pos);
         if (task == task_name) {
            path = s.substr(pos + 1);
            break;
         }
      }
      cache_in.close();
      if (!path.empty()) {
         std::vector<Task*> ans = getAllTaskNodes({ path + "/TASK" }, false);
         // Verify that the task name has not changed.
         if (ans[0]->name == task_name) {
            return ans;
         }
      }
   }
   
   // Otherwise, return all tasks in directory (and generate cache).
   std::vector<std::string> paths_to_tasks = findAllPathsInDir();
   return getAllTaskNodes(paths_to_tasks, /* create_cache= */ true);
}

void deleteTasks(const std::vector<Task*>& tasks) {
   for (Task * task : tasks) {
      delete task;
   }
}

int main(int argc, char *argv[]) {   
   std::vector<Task*> tasks;
   bool found_error = false;
   try {
      if (argc > 1) {
         std::string arg(argv[1]);
         std::size_t found = arg.find(':');
         std::string task_name = found == std::string::npos ? arg : arg.substr(0, found);
         std::string solution_name = found == std::string::npos ? "" : arg.substr(found + 1);
         tasks = getTasksFor(task_name);
         generateFileForTasksFilterByTaskAndSolution(tasks, task_name, solution_name);
      } else {
         std::vector<std::string> paths_to_tasks = findAllPathsInDir();
         tasks = getAllTaskNodes(paths_to_tasks, /* create_cache= */ true);
         generateFileForTasks(tasks);
      }
   } catch (std::exception& ex) {
      // std::cout << ex.what() << std::endl;
      found_error = true;
   }
   deleteTasks(tasks);
   return found_error;
}
