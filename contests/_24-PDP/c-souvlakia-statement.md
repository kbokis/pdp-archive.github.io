---
layout: statement
codename: souvlakia
---

Ο κ. Παπαδόπουλος απολύθηκε από το εστιατόριο που δούλευε και αποφάσισε να ανοίξει ένα σουβλατζίδικο για διανομή κατ'οίκον στην συνοικία «Σύγχρονες Κατοικίες». Θέλει να επιλέξει την καλύτερη θέση για το κατάστημά του. Οι κόμβοι του παρακάτω σχήματος δείχνουν τις πιθανές επιλογές του.

![Παράδειγμα](/assets/24-pdp-c-souvlakia-example.jpg){:width="400px"}

Μπορεί να επιλέξει για να νοικιάσει ένα κατάστημα σε μία από τις εννέα θέσεις που βρίσκονται πιθανά καταστήματα για ενοικίαση. Όμως διαμερίσματα με κατοίκους υπάρχουν μόνο σε τρεις από αυτές τις θέσεις ($$A$$, $$B$$, $$\Gamma$$ ή στις θέσεις $$2$$, $$5$$, και $$9$$). Tα πιθανά σημεία συνδέονται μεταξύ τους με δρόμους όπως δείχνει το σχήμα με τις αντίστοιχες αποστάσεις. 

Οι πελάτες συνηθίζουν να ψωνίζουν από το κοντινότερο κατάστημα. Aν επιλέξει τη θέση $$1$$, τότε οι ελάχιστες αποστάσεις από τα $$A$$, $$B$$ και $$\Gamma$$ είναι αντίστοιχα $$4$$, $$8$$ και $$9$$, ενώ αν επιλέξει τη θέση $$7$$, οι αντίστοιχες ελάχιστες αποστάσεις είναι $$13$$, $$9$$ και $$12$$. Aν επιλέξει τη θέση $$6$$, τότε οι ελάχιστες αποστάσεις από τα $$A$$, $$B$$ και $$\Gamma$$ είναι αντίστοιχα $$9$$, $$7$$ και $$4$$, που είναι όλες καλύτερες από αυτές της θέσης $$7$$, αλλά όχι και από αυτές της θέσης $$1$$ (η θέση $$1$$ είναι καλύτερη ως προς την απόσταση από το $$A$$).

Για να επιλέξει λοιπόν την καταλληλότερη θέση για το κατάστημα, ο κ. Παπαδόπουλος αποφασίζει να εξετάζει υποψήφιες θέσεις και να αποκλείει όσες υπολείπονται κάποιας άλλης θέσης ως προς τις τρεις αποστάσεις από τα $$A$$, $$B$$, και $$\Gamma$$. Συγκεκριμένα, μια θέση $$p$$, με ελάχιστες αποστάσεις $$a$$, $$b$$, $$c$$ από τα $$A$$, $$B$$, $$\Gamma$$, αποκλείεται αν υπάρχει θέση $$q$$, με ελάχιστες αποστάσεις $$x$$, $$y$$, $$z$$ από τα $$A$$, $$B$$, $$\Gamma$$, για τις οποίες ισχύει ότι $$a > x$$, $$b > y$$, και $$c > z$$.

## Πρόβλημα

Nα αναπτύξετε ένα πρόγραμμα σε μια από τις γλώσσες του ΙΟΙ το οποίο: αφού διαβάσει τα μήκη των δρόμων που συνδέουν τις θέσεις των πιθανών καταστημάτων και τις θέσεις $$A$$, $$B$$, $$\Gamma$$, όπου υπάρχουν κάτοικοι, θα διαβάζει μια ακολουθία θέσεων και θα απαντά αν με βάση τον παραπάνω κανόνα, καθεμία από αυτές είναι υποψήφια για το κατάστημα ή όχι. Θα γίνει ερώτηση για παραπάνω από μία πιθανές θέσεις, ενώ μπορεί να γίνει ερώτηση και για τις θέσεις $$A$$, $$B$$, και $$\Gamma$$.

## Aρχεία εισόδου

Τα αρχεία εισόδου, με όνομα **souvlakia.in**, είναι αρχεία κειμένου με την εξής δομή: Στην πρώτη γραμμή έχουν δύο ακέραιους χωρισμένους μεταξύ τους με ένα κενό διάστημα: έναν ακέραιο αριθμό $$N$$ ($$3 \leq N \leq 100.000$$), το πλήθος των υποψήφιων θέσεων, και έναν ακέραιο αριθμό $$M$$ ($$3 \leq M \leq 400.000$$), το πλήθος των δρόμων που συνδέουν αυτές τις θέσεις. Σε καθεμία από τις επόμενες $$Μ$$ γραμμές, υπάρχουν τρεις ακέραιοι, χωρισμένοι μεταξύ τους με ένα κενό διάστημα, που αναπαριστούν έναν δρόμο: οι δύο πρώτοι αντιστοιχούν στα δύο άκρα του δρόμου, και ο τρίτος στο μήκος του δρόμου $$d$$ ($$1 \leq d \leq 20.000$$). Aκολούθως, στη γραμμή $$M+2$$, τέσσερις ακέραιοι, χωρισμένοι με κενό: οι τρεις πρώτοι αντιστοιχούν στις τρεις θέσεις $$A$$, $$B$$, και $$\Gamma$$, και ο τέταρτος ακέραιος $$L$$ ($$1 \leq L \leq 50.000$$) παριστάνει το πλήθος των ερωτήσεων που ακολουθούν. Σε καθεμία από τις επόμενες $$L$$ γραμμές, υπάρχει ένας ακέραιος που αντιστοιχεί σε μια υποψήφια θέση που θέλουμε να ελεγχθεί. 

Όλοι οι δρόμοι θεωρούνται διπλής κατεύθυνσης. Επίσης, δε θα υπάρχουν δύο διαφορετικοί δρόμοι που να έχουν τα ίδια άκρα.

## Aρχεία εξόδου

Τα αρχεία εξόδου με το όνομα **souvlakia.out** είναι αρχεία κειμένουμε την εξής δομή: Περιέχουν $$L$$ γραμμές, σε κάθε μία από τις οποίες βρίσκεται η απάντηση σε μία από τις ερωτήσεις, με την ίδια σειρά. Κάθε απάντηση θα είναι «YES», αν ο κ. Παπαδόπουλος μπορεί να ανοίξει το κατάστημά του στην αντίστοιχη θέση, διαφορετικά «NΟ».

## Παράδειγμα αρχείων εισόδου - εξόδου

| **souvlakia.in**                         | **souvlakia.out** |
| ------------------------------------ | ------------- |
| 9 15 <br> 1 2 4 <br> 2 5 4 <br> 1 3 8 <br> 2 4 7 <br> 2 6 11 <br> 3 4 1 <br> 4 6 2 <br> 5 6 7 <br> 3 9 1 <br> 4 9 6 <br> 6 9 4 <br> 8 9 2 <br> 6 7 14 <br> 5 7 9 <br> 8 7 10 <br> 2 5 9 9 <br> 1 <br> 2 <br> 3 <br> 4 <br> 5 <br> 6 <br> 7 <br> 8 <br> 9 | YES <br> YES <br> YES <br> YES <br> YES <br> YES <br> NO <br> NO  <br> YES | 


## Όρια

**Μορφοποίηση:** Στην έξοδο, όλες οι γραμμές τερματίζουν με ένα χαρακτήρα newline. \\
**Μέγιστος χρόνος εκτέλεσης:** $$1$$ sec \\
**Μέγιστη διαθέσιμη μνήμη:** $$64$$ MB

Για $$30\%$$ της βαθμολογίας, θα είναι $$N \leq 2.000$$, $$M \leq 15.000$$ και $$L \leq 1.000$$.
