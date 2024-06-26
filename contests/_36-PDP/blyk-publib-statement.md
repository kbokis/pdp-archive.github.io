---
layout: statement
codename: publib
---

Δίνεται ο οδικός χάρτης ενός απομακρυσμένου νησιού της χώρας. Στο
νησί υπάρχουν $$N$$ χωριά (αριθμημένα από $$1$$ μέχρι $$N$$) που συνδέονται
μεταξύ τους με $$M$$ δρόμους, καθένας από τους οποίους είναι διπλής
κατεύθυνσης και συνδέει μεταξύ τους δύο χωριά. Θεωρήστε δεδομένο
ότι είναι δυνατόν να μεταβεί κανείς από οποιοδήποτε χωριό του νησιού
σε οποιοδήποτε άλλο, μέσω των δρόμων του οδικού δικτύου.

Στο νησί μέχρι σήμερα δεν υπάρχει δημόσια βιβλιοθήκη. Ιδανικά, κάθε
χωριό θα έπρεπε να έχει τη δική του. Όμως τα χρήματα του δημόσιου
ταμείου φτάνουν για μία μόνο δημόσια βιβλιοθήκη, που θα πρέπει
αναγκαστικά θα τοποθετηθεί σε ένα από τα χωριά του νησιού.

Ονομάζουμε “απόσταση” ενός χωριού από τη βιβλιοθήκη το ελάχιστο
πλήθος των δρόμων που πρέπει να διανύσουμε για να φτάσουμε από
το χωριό σε αυτήν (δηλαδή, το πλήθος των ακμών στο συντομότερο
μονοπάτι). Για παράδειγμα, αν η βιβλιοθήκη τοποθετηθεί στο χωριό 1,
τότε το χωριό 1 βρίσκεται σε απόσταση 0 από τη βιβλιοθήκη. Αν το
χωριό 2 είναι γειτονικό του 1 (δηλαδή συνδέεται απευθείας με αυτό με
έναν δρόμο), τότε το χωριό 2 βρίσκεται σε απόσταση 1 από τη
βιβλιοθήκη. Αν το χωριό 3 είναι γειτονικό του 2 αλλά όχι γειτονικό του
1 (δηλαδή συνδέεται απευθείας με το χωριό 2 αλλά όχι με το χωριό
1), τότε το χωριό 3 βρίσκεται σε απόσταση 2 από τη βιβλιοθήκη. Και
ούτω καθεξής.

Θέλουμε να τοποθετήσουμε τη βιβλιοθήκη έτσι ώστε η απόσταση του
πιο μακρινού χωριού από αυτήν να είναι η ελάχιστη δυνατή.


## Πρόβλημα

Να αναπτύξετε ένα πρόγραμμα σε μια από τις γλώσσες του IOI
(PASCAL, C, C++, Java) το οποίο θα διαβάζει τον οδικό χάρτη του
νησιού και θα εκτυπώνει την απόσταση του πιο μακρινού χωριού από
τη βιβλιοθήκη, αν τοποθετήσουμε αυτή στην καλύτερη δυνατή θέση.


## Αρχεία εισόδου:

Τα αρχεία εισόδου με όνομα **publib.in** είναι αρχεία κειμένου με την
εξής δομή: <!-- Τα bullets προστέθηκαν για την αποφυγή των δύο ":" στο ίδιο επίπεδο. -->
 - Στην πρώτη γραμμή υπάρχουν δύο θετικοί ακέραιοι αριθμοί χωρισμένοι μεταξύ τους με ένα κενό διάστημα: το πλήθος των χωριών $$N$$ και το πλήθος των δρόμων $$M$$ που τα συνδέουν. 
 - Κάθε μία από τις επόμενες $$M$$ γραμμές θα περιέχει δύο θετικούς ακέραιους αριθμούς $$U_i$$ και $$V_i$$, χωρισμένους με ένα κενό διάστημα: τους αριθμούς των χωριών που αντιστοιχούν στα δύο άκρα ενός δρόμου.

## Αρχεία εξόδου:

Τα αρχεία εξόδου με όνομα **publib.out** είναι αρχεία κειμένου με την
εξής δομή. Πρέπει να περιέχουν ακριβώς μία γραμμή που να περιέχει
ακριβώς έναν ακέραιο αριθμό: την απόσταση του πιο μακρινού χωριού
από τη βιβλιοθήκη, αν τοποθετήσουμε αυτή στην καλύτερη δυνατή
θέση.

## Περιορισμοί:

 - $$1 \leq N ≤ 2.000$$, $$1 \leq M \leq 40.000$$ και $$N \times M \leq 10.000.000$$.
 - $$1 \leq U_i \leq N$$, $$1 \leq V_i \leq N$$, και $$U_i \neq V_i$$, για κάθε $$i$$, όπου $$1 \leq i \leq M$$
 - δεν θα δίνονται δύο δρόμοι που να συνδέουν τα ίδια χωριά

## Παράδειγμα αρχείων εισόδου-εξόδου:

| **publib.in**      | **publib.out** |
| :--- | :--- |
| 8 9<br>8 6<br>4 2<br>1 5<br>8 1<br>3 7<br>4 6<br>5 2<br>7 1<br>2 8 | 3 |

<img style="float: right" src="/assets/36-bgym-publib.png"/>

*Επεξήγηση παραδείγματος:* Ο οδικός χάρτης του παραδείγματος φαίνεται στο σχήμα
δεξιά. <!-- Αρχικά: "στο σχήμα της προηγούμενης σελίδας." -->
Αν τοποθετήσουμε τη βιβλιοθήκη στο χωριό 1,
τότε το πιο μακρινό από αυτήν χωριό είναι το 4 και η απόσταση αυτού
είναι 3 (π.χ. ακολουθώντας τους δρόμους 4-6, 6-8, 8-1). Ομοίως αν
τοποθετήσουμε τη βιβλιοθήκη σε κάποιο από τα χωριά 5 ή 8: και στις
δύο περιπτώσεις, το πιο μακρινό από αυτή χωριό είναι το 3 και η
απόσταση αυτού είναι 3. Δεν υπάρχει τρόπος να τοποθετήσουμε τη
βιβλιοθήκη έτσι ώστε το πιο μακρινό χωριό να έχει απόσταση
μικρότερη του 3.

## Παρατηρήσεις:

**Μορφοποίηση**: Στην είσοδο αλλά και στην έξοδο, κάθε γραμμή τερματίζει με έναν χαρακτήρα newline.<br>
**Μέγιστος χρόνος εκτέλεσης**: $$1$$ sec.<br>
**Μέγιστη διαθέσιμη μνήμη**: $$64$$ MB.
