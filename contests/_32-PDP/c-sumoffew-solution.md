---
layout: solution
codename: sumoffew
---

Παρακάτω εξετάζουμε διάφορες λύσεις διαβαθμισμένης δυσκολίας. Ας σημειωθεί ότι
δεν είναι οι μοναδικές λύσεις που θα μπορούσε να σκεφτεί κανείς. Άλλες λύσεις
μπορούν να προκύψουν για παράδειγμα με διαφορετικό συνδυασμό των ιδεών που
ακολουθούν.

### Πολύ αργή λύση --- $$\mathcal{O}(N^3)$$

Η πρώτη προσέγγιση που σκέφτεται κανείς σε κάθε πρόβλημα είναι η brute force,
δηλαδή η δοκιμή όλων των υποψήφιων έγκυρων απαντήσεων ώστε να βρούμε τη
βέλτιστη.  Στο συγκεκριμένο πρόβλημα, αυτό σημαίνει να απαριθμήσουμε κάθε δυνατό
συνδυασμό από $$i \leq j$$ και να ελέγξουμε αν η ακολουθία $$x_i, x_{i+1},
\ldots x_{j}$$ είναι *έγκυρη* --- αν δηλαδή αποτελείται από $$K$$ ή λιγότερους
διαφορετικούς αριθμούς --- και αν είναι, υπολογίζουμε το άθροισμα των όρων της.
Τέλος, τυπώνουμε το μέγιστο άθροισμα έγκυρης ακολουθίας που είδαμε.

Πώς όμως μπορούμε να ελέγξουμε αν μια ακολουθία είναι έγκυρη; Ας σκεφτούμε πρώτα
την απλή περίπτωση όπου οι όροι της ακολουθίας δεν είναι πολύ μεγάλοι ($$x_i
\leq 1.000.000$$). Σε αυτή την περίπτωση μπορούμε να κρατάμε έναν πίνακα
συχνοτήτων `freq` με $$1.000.000$$ θέσεις όπου η θέση $$s$$ θα διατηρεί το
πλήθος των εμφανίσεων του αριθμού $$s$$ στην ακολουθία. Μπορούμε συνεπώς με ένα
πέρασμα της ακολουθίας $$x_i, \ldots, x_j$$ να ανανεώνουμε τον πίνακα `freq` και
ταυτόχρονα όταν βλέπουμε ότι η συχνότητα ενός αριθμού αυξήθηκε από $$0$$ σε
$$1$$, να αυξάνουμε ένα μετρητή `c` ώστε να θυμόμαστε πόσους διαφορετικούς
αριθμούς έχουμε δει μέχρι στιγμής. Παράλληλα, στο ίδιο for loop, μπορούμε να
υπολογίζουμε το άθροισμα της ακολουθίας. 

**Πολυπλοκότητα**: Υπάρχουν $$N \cdot (N-1) / 2 = \mathcal{O}(N^2)$$ διαστήματα
προς έλεγχο και χρειαζόμαστε χρόνο $$\mathcal{O}(N)$$ για να διαπεράσουμε το
καθένα και να ελέγξουμε αν είναι έγκυρο. Συνεπώς, η λύση έχει πολυπλοκότητα
$$\mathcal{O}(N^3)$$.

Ενδεικτική υλοποίηση:

{% include code.md solution_name='sumoffew-n3.cpp' %}

### Αργή λύση --- $$\mathcal{O}(N^2 \log{N})$$ ή $$\mathcal{O}(N^2)$$

Ένας λόγος που η προηγούμενη λύση δεν είναι αποδοτική είναι επειδή επαναλαμβάνει
υπολογισμούς χωρίς λόγο. Αν το σκεφτούμε, δεν υπάρχει λόγος να ξεκινάμε τον
έλεγχο εγκυρότητας από την αρχή κάθε φορά που προστίθεται ένας μόνο νέος αριθμός
στην υποψήφια ακολουθία. Μπορούμε πολύ πιο απλά να μη μηδενίζουμε τον πίνακα
`freq` όταν αυξάνεται η τιμή του $$j$$ αλλά να τον ανανεώνουμε με βάση την νέα
τιμή.  Έτσι, γλιτώνουμε το εσωτερικό for loop.

Άλλο ένα σημείο που πρέπει να σκεφτούμε είναι πώς να χειριστούμε αριθμούς
μεγαλύτερους από $$1.000.000$$. Ξέρουμε ότι το άθροισμα όλων των αριθμών δεν θα
υπερβαίνει το $$1.000.000.000$$, συνεπώς και κάθε ένας από τους αριθμούς
ξεχωριστά δεν θα υπερβαίνει αυτό το όριο εφόσον οι αριθμοί είναι θετικοί. Αν
απλά αυξήσουμε το μέγεθος του πίνακα `freq` τότε χρειάζεται να δεσμεύσουμε μνήμη
για $$1.000.000.000$$ ακεραίους, κάθε ένας μεγέθους 4 byte, συνεπώς θα
χρειαζόμασταν περίπου $$4$$ GB μνήμης!

Για να λύσουμε αυτό το πρόβλημα, μπορούμε αντί για πίνακα να χρησιμοποιήσουμε
ένα `map`/`unordered_map` της C++. Ουσιαστικά ένα map συμπεριφέρεται σαν array
αλλά δεσμεύει χώρο μόνο για τα στοιχεία που έχουν μη-μηδενικές τιμές. Η
πολυπλοκότητα ανάγνωσης/εγγραφής ενός στοιχείου σε ένα `unordered_map`
(αντίστοιχα `map`) είναι $$\mathcal{O}(1)$$ (αντίστοιχα
$$\mathcal{O}(\log{N})$$). Για περισσότερες πληροφορίες σχετικά με αυτά τα
containers, google is your friend :) (ή ρίξτε μια ματιά <a target="_blank"
href="https://kallinikos.github.io/Hash-Table">εδώ</a>).

Μια υλοποίηση με map μπορούμε να δούμε παρακάτω με πολυπλοκότητα
$$\mathcal{O}(N^2 \log{N})$$. Σύμφωνα με την εκφώνηση, αυτή η λύση θα πρέπει να
βαθμολογείται με τουλάχιστον $$50\%$$.

{% include code.md solution_name='sumoffew-n2.cpp' %}

### Βέλτιστη λύση --- $$\mathcal{O}(N)$$

Θα χρησιμοποιήσουμε την τεχνική του sliding window (ή two pointers) η οποία
βασίζεται στην εξής ιδέα: Στην $$\mathcal{O}(N^2)$$ λύση που μόλις είδαμε, κάθε
φορά που αυξάνουμε το δείκτη $$i$$, ξεκινάμε την αναζήτηση για πιθανά $$j$$ από
την αρχή. Θα μπορούσαμε όμως να θυμόμαστε την τελευταία τιμή του $$j$$ από την
προηγούμενη επανάληψη και να ξεκινήσουμε από εκεί. Ο λόγος είναι πως ακόμα και
αν υπάρχουν έγκυρες λύσεις για μικρότερα $$j$$, θα έχουν μικρότερο άθροισμα από
τις λύσεις που έχουμε δει μέχρι στιγμής και συνεπώς αποκλείεται να είναι
βέλτιστες!

Με άλλα λόγια: Κάθε
στιγμή, διατηρούμε δύο δείκτες (two pointers) $$i, j$$ που ορίζουν ένα διάστημα
(window) με μια υποψήφια λύση. Σε κάθε επανάληψη προσπαθούμε να αυξήσουμε τον
δεξί δείκτη όσο μπορούμε διατηρώντας την τρέχουσα λύση έγκυρη. Μόλις η λύση
πάψει να είναι έγκυρη, αρχίζουμε να αυξάνουμε τον αριστερό δείκτη μέχρι να βρω
και πάλι έγκυρη λύση. Η τεχνική αυτή ονομάζεται sliding window γιατί μοιάζει σαν
να "σέρνει" προς τα δεξιά ένα υποψήφιο διάστημα.

**Πολυπλοκότητα**: Επειδή σε κάθε βήμα, τουλάχιστον ένας από τους δείκτες $$i,
j$$ αυξάνεται κατά 1, το συνολικό πλήθος των επαναλήψεων δεν μπορεί να είναι
μεγαλύτερο από $$2N$$. Επιπλέον, σε κάθε επανάληψη μπορούμε να ανανεώνουμε τις
μεταβλητές `freq`, `c`, `sum` ώστε να έχουν τις σωστές τιμές για το τρέχον
διάστημα σε σταθερό χρόνο. Συνεπώς η συνολική πολυπλοκότητα είναι
$$\mathcal{O}(N)$$.

Παρακάτω δίνεται μια ενδεικτική υλοποίηση η οποία περνάει το $$100\%$$ των test
cases:

{% include code.md solution_name='sumoffew-n.cpp' %}

*Σημείωση*: Αν στην παραπάνω λύση χρησιμοποιούσαμε `array` αντί για
`map`/`unordered_map` τότε, σύμφωνα με την εκφώνηση, θα βαθμολογούμασταν με
τουλάχιστον $$70\%$$.