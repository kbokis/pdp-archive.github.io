---
layout: statement
codename: roadwork
---

Η εθνική οδός είναι στα κακά της χάλια. Το οδόστρωμα έχει φθαρεί και χρειάζεται άμεσα επισκευή. Το συνεργείο που έχει αναλάβει την επισκευή δυστυχώς δεν είναι πολύ οργανωμένο. Κάθε μέρα, ξεκινάει να επισκευάσει ένα συνεχόμενο τμήμα του δρόμου, το οποίο γνωρίζουμε πού αρχίζει και πού τελειώνει. Όμως, κάποια επόμενη μέρα είναι πιθανό να επισκευάσει πάλι ένα τμήμα που έχει ήδη, πλήρως ή μερικώς, επισκευαστεί!

Η εθνική οδός έχει συνολικό μήκος $$L$$ χιλιόμετρα. Το συνεργείο έχει προγραμματίσει να δουλέψει $$N$$ μέρες και, την $$k$$-οστή μέρα, έχει προγραμματίσει να επισκευάσει το τμήμα του δρόμου που εκτείνεται από τη θέση $$S_k$$ έως τη θέση $$T_k$$. Το υπουργείο δημοσίων έργων θέλει να ολοκληρωθεί η επισκευή το συντομότερο. Θέλει να ξέρει μετά από πόσες μέρες το μεγαλύτερο συνεχόμενο τμήμα του δρόμου που δεν έχει ακόμη επισκευαστεί δε θα είναι μεγαλύτερο από $$X$$.

## Πρόβλημα

Nα γραφεί ένα πρόγραμμα σε μια από τις γλώσσες του ΙΟΙ το οποίο, δεδομένου του μήκους L του δρόμου, του προγράμματος του συνεργείου επισκευής $$(N, S_k, T_k)$$ και του αριθμού $$X$$ θα βρίσκει τον ελάχιστο αριθμό ημερών που πρέπει να εργαστεί το συνεργείο ώστε το μήκος του μεγαλύτερου συνεχόμενου τμήματος του δρόμου που δεν έχει ακόμη επισκευαστεί να μην υπερβαίνει το $$X$$. Αν αυτό δεν πρόκειται να συμβεί ποτέ βάσει του προγράμματος του συνεργείου, το πρόγραμμά σας πρέπει να εκτυπώνει τον αριθμό $$-1$$.

## Aρχεία εισόδου

Τα αρχεία εισόδου με όνομα **roadwork.in** είναι αρχεία κειμένου με την εξής δομή: Στην πρώτη γραμμή έχουν τρεις ακέραιους αριθμούς: $$N$$ $$(1 \leq N \leq 1.000.000)$$, $$L$$ ($$1 \leq L \leq 1.000.000.000$$) και $$X$$ ($$0 \leq X \leq L$$), χωρισμένους ανά δύο με ένα κενό διάστημα. Ακολουθούν $$N$$ γραμμές, κάθε μία από τις οποίες περιέχει δύο ακέραιους αριθμούς $$S_k$$, $$T_k$$ ($$0 \leq S_k \leq T_k \leq L$$), χωρισμένους μεταξύ τους με ένα κενό διάστημα.

## Aρχεία εξόδου

Τα αρχεία εξόδου με όνομα **roadwork.out** είναι αρχεία κειμένου με την εξής δομή: Έχουν μια μόνο γραμμή που περιέχει μόνο έναν ακέραιο αριθμό $$D$$ ($$-1 \leq D \leq N$$).

## Παραδείγματα αρχείων εισόδου - εξόδου

**1<sup>o</sup>**

| **roadwork.in**                         | **roadwork.out** |
| ------------------------------------ | ------------- |
| 4 30 6 <br> 1 5 <br> 11 27 <br> 2 14 <br> 18 28 | 2 |

**2<sup>o</sup>**

| **roadwork.in**                         | **roadwork.out** |
| ------------------------------------ | ------------- |
| 4 30 1 <br> 1 5 <br> 11 27 <br> 2 14 <br> 18 28 | -1 |

*Επεξήγηση παραδειγμάτων:* Και στα δύο παραδείγματα, το μήκος του δρόμου και το πρόγραμμα του συνεργείου είναι τα ίδια και διαφέρει μόνο το $$X$$. Μετά την πρώτη μέρα, το μεγαλύτερο συνεχόμενο τμήμα του δρόμου που δεν έχει ακόμη επισκευαστεί έχει μήκος $$25$$ (από τη θέση $$5$$ έως τη θέση $$30$$). Μετά τη δεύτερη μέρα έχει μήκος $$6$$ (από τη θέση $$5$$ έως τη θέση $$11$$). Μετά την τρίτη μέρα έχει μήκος $$3$$ (από τη θέση $$27$$ έως τη θέση $$30$$) και μετά την τέταρτη μέρα έχει μήκος $$2$$ (από τη θέση $$28$$ έως τη θέση $$30$$). Άρα, η σωστή απάντηση για το 1<sup>ο</sup> παράδειγμα είναι $$2$$ (μετά τη δεύτερη μέρα το μήκος του μεγαλύτερου συνεχόμενου τμήματος του δρόμου δε θα υπερβαίνει το $$X=6$$), ενώ για το 2<sup>ο</sup> παράδειγμα η σωστή απάντηση είναι $$-1$$ (το μήκος του μεγαλύτερου συνεχόμενου τμήματος του δρόμου που δεν έχει επισκευαστεί ποτέ δε θα γίνει ίσο με $$X=1$$ ή λιγότερο).

**Μορφοποίηση:** Στην έξοδο, όλες οι γραμμές τερματίζουν με ένα χαρακτήρα newline. <br>
**Μέγιστος χρόνος εκτέλεσης:** $$2$$ sec. <br>
**Μέγιστη διαθέσιμη μνήμη:** $$64$$ MB.
