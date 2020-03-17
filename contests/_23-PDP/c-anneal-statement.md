---
layout: statement
codename: anneal
---

Το γυαλί παράγεται λιωμένο σε φούρνους τήξης, όπου επικρατούν πολύ υψηλές θερμοκρασίες, και ψύχεται σταδιακά, ομοιόμορφα, και με ελεγχόμενο τρόπο, ώστε να αποφευχθούν σπασίματα ή ρωγμές, και να διατηρηθεί υψηλή η ποιότητα του παραγόμενου προϊόντος. Μια εταιρεία παραγωγής γυαλιού διαθέτει μια σειρά από $$N$$ θαλάμους ψύξης και ψύχει το προϊόν περνώντας τον διαδοχικά από όλους αυτούς. Οι θάλαμοι βρίσκονται σε μια ευθεία γραμμή και αριθμούνται κατά μήκος αυτής, ξεκινώντας από τον πλησιέστερο στο φούρνο τήξης. Πριν ξεκινήσει η διαδικασία παραγωγής, είναι γνωστή η θερμοκρασία $$a_i$$ που επικρατεί σε κάθε θάλαμο ψύξης $$i$$. Για να προχωρήσει η διαδικασία ψύξης χωρίς προβλήματα, φροντίζουμε ώστε καθώς το γυαλί περνά από τον ένα θάλαμο στον επόμενο, να μην έχουμε αύξηση της θερμοκρασίας. Αυτό επιτυγχάνεται είτε μειώνοντας τη θερμοκρασία ενός θαλάμου $$i$$ από $$a_i$$ σε $$b_i$$, το οποίο απαιτεί ενέργεια ίση με τη διαφορά θερμοκρασίας $$a_i - b_i$$, είτε παρακάμπτοντας τον θάλαμο $$i$$, το οποίο απαιτεί ενέργεια ίση με το διπλάσιο της θερμοκρασίας $$a_i$$. Η υπάρχουσα υποδομή της εταιρείας δεν επιτρέπει ούτε την αύξηση της θερμοκρασίας ενός θαλάμου, ούτε οποιαδήποτε αντιμετάθεσή των θαλάμων στη σειρά με την οποία διέρχεται το γυαλί από αυτούς (δεν μπορεί δηλαδή το γυαλί να περάσει πρώτα από κάποιον θάλαμο $$j > i$$ και εν συνεχεία να περάσει από τον θάλαμο $$i$$).

Ζητείται το ελάχιστο απαιτούμενο ποσό ενέργειας για να έχουμε μια σειρά θαλάμων κατά μήκος της οποίας η θερμοκρασία δεν αυξάνεται.

## Αρχεία εισόδου

Η πρώτη γραμμή της εισόδου θα περιέχει ακριβώς έναν ακέραιο αριθμό: το πλήθος των θαλάμων N. Η δεύτερη γραμμή θα περιέχει $$N$$ θετικούς ακέραιους αριθμούς $$a_1, ... a_N$$ χωρισμένους μεταξύ τους με κενά διαστήματα: τις αρχικές θερμοκρασίες των θαλάμων.

## Αρχεία εξόδου

Η έξοδος πρέπει να αποτελείται από μία γραμμή που να περιέχει ακριβώς έναν ακέραιο αριθμό: Το ελάχιστο απαιτούμενο ποσό ενέργειας για να έχουμε μια σειρά θαλάμων κατά μήκος της οποίας η θερμοκρασία δεν αυξάνεται.

## Παράδειγμα αρχείων εισόδου - εξόδου

| **anneal.in**                         | **anneal.out** |
| ------------------------------------ | ------------- |
| 8 <br> 55 10 80 50 20 40 70 60 | 135 |

*Επεξήγηση Παραδείγματος:*
Παρακάμπτουμε τον $$2$$ο και τον $$5$$ο θάλαμο, και μειώνουμε τη θερμοκρασία του 3ου θαλάμου σε $$55$$, και των θαλάμων $$7$$ και $$8$$ σε $$40$$. Η ακολουθία θερμοκρασιών που προκύπτει είναι $$[55, x, 55, 50, x, 40, 40, 40]$$, όπου το $$x$$ δηλώνει τους θαλάμους που έχουν παρακαμφθεί. Το ενεργειακό κόστος είναι: $$(80–55) + (70–40) + (60–40) = 75$$ για την μείωση της θερμοκρασίας στους θαλάμους $$3$$, $$7$$ και $$8$$ αντίστοιχα, και $$2 \cdot 10 + 2 \cdot 20 = 60$$ για τους θαλάμους $$2$$ και $$5$$, αντίστοιχα, που παρακάμψαμε.

## Περιορισμοί

 * $$2 \leq N \leq 50.000$$.
 * $$1 \leq a_i \leq 10.000.000$$.
 * **Όριο χρόνου εκτέλεσης:** $$1$$ sec.