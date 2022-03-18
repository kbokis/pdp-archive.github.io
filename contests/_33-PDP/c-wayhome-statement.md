---
layout: statement
codename: wayhome
---

Είναι άλλη μια συνηθισμένη μέρα μέσα στην καραντίνα. Ως σωστοί προγραμματιστές έχετε φάει όλη σας τη μέρα να ψάχνετε ένα ύπουλο bug και αποφασίζετε να πάτε έναν απογευματινό περίπατο για να σκεφτείτε πιο καθαρά. 
Απορροφημένοι στη σκέψη σας όμως, χάνετε την αίσθηση του χρόνου. Η ώρα είναι 9 και η απαγόρευση κυκλοφορίας μόλις αρχίζει. 
Γνωρίζετε ότι στις 9 ακριβώς ένας αστυνόμος ξεκινάει την περιπολία του από το αστυνομικό τμήμα του δήμου και, αν σας δει, θα σας επιβάλει ένα βαρύ πρόστιμο. Θέλετε να γυρίσετε στο σπίτι γλιτώνοντας το πρόστιμο. 
Είναι η ευκαιρία σας να αξιοποιήσετε τις αλγοριθμικές γνώσεις που έχετε αποκτήσει όλον αυτόν τον καιρό μέσα στην καραντίνα!

Ο χάρτης του δήμου σας αναπαρίσταται με ένα πλέγμα διαστάσεων $$N \times M$$. Κάθε τετράγωνο του πλέγματος μπορεί να είναι δρόμος ή κτίριο.
Επιπλέον είναι γνωστή η αρχική σας θέση, η θέση του αστυνομικού τμήματος και η θέση του σπιτιού σας.

Πρέπει να σκεφτείτε μια <u>προκαθορισμένη</u> διαδρομή που να ξεκινάει από την αρχική σας θέση, να καταλήγει στο σπίτι σας και να αποτελείται από μια ακολουθία κινήσεων. 
Σε κάθε κίνηση μπορείτε να προχωρήσετε μόνο (οριζόντια ή κατακόρυφα) σε κάποιο γειτονικό τετράγωνο που δεν είναι κτίριο. 
Ταυτόχρονα ο αστυνομικός μπορεί να κινηθεί με παρόμοιο τρόπο ή να μείνει ακίνητος. Η κίνησή σας μαζί με την αντίδραση του αστυνομικού ολοκληρώνονται σε ένα λεπτό.

Μετά από κάθε λεπτό μπορούν να συμβούν τα εξής:
* Αν είστε στο οπτικό πεδίο του αστυνομικού, δηλαδή στην ίδια γραμμή (οριζόντια) ή στήλη (κατακόρυφα) χωρίς κάποιο κτίριο ανάμεσά σας, τότε παίρνετε πρόστιμο.
* Αν δεν έχετε πάρει πρόστιμο και είστε στο σπίτι σας, τότε μπαίνετε μέσα ασφαλείς.

## Πρόβλημα:

Να αναπτύξετε ένα πρόγραμμα σε μια από τις γλώσσες του IOI (PASCAL, C, C++, Java) το οποίο θα διαβάζει την περιγραφή του δήμου σας και θα αποφασίζει αν υπάρχει <u>προκαθορισμένη</u> διαδρομή η οποία να οδηγεί στο σπίτι σας με ασφάλεια, ανεξάρτητα από το πως κινείται ο αστυνόμος.

## Αρχεία Εισόδου:

Το αρχείο εισόδου με όνομα **wayhome.in** είναι αρχείο κειμένου με την εξής δομή. Η πρώτη γραμμή περιέχει έναν ακέραιο αριθμό $$T$$, τον αριθμό των σεναρίων του προβλήματος. Στη συνέχεια ακολουθούν T σενάρια, κάθε ένα με την παρακάτω δομή.
Η πρώτη γραμμή περιέχει δύο ακέραιους αριθμούς $$N$$, $$M$$, τις διαστάσεις του δήμου. Κάθε μια από τις επόμενες $$N$$ γραμμές περιέχει $$M$$ χαρακτήρες, που περιγράφουν τα αντίστοιχα τετράγωνα. 
Κάθε χαρακτήρας μπορεί να είναι είτε <b>.</b> (δρόμος), <b>#</b> (κτίριο), <b>Y</b> (η θέση σας), <b>P</b> (η θέση του αστυνομικού), ή <b>H</b> (η θέση του σπιτιού).
Θεωρήστε δεδομένο ότι κάθε χαρακτήρας από τους Y, P και H θα εμφανίζεται ακριβώς μια φορά και θα μπορεί να χρησιμοποιηθεί ως δρόμος για τις μετακινήσεις.

## Αρχεία Εξόδου:

Το αρχείο εξόδου με όνομα **wayhome.out** είναι αρχείο κειμένου με την εξής δομή. Αποτελείται από Τ γραμμές, κάθε μια από τις οποίες αντιστοιχεί στην απάντηση ενός σεναρίου και περιέχει ακριβώς μια συμβολοσειρά: <b>YES</b> αν υπάρχει ασφαλής διαδρομή προς το σπίτι και <b>NO</b> διαφορετικά.


## Παράδειγμα Αρχείου εισόδου - εξόδου:

| **wayhome.in**      | **wayhome.out** |
| :--- | :--- |
| 3<br>5 7<br>Y\.\.\.\.\.P<br>\.\.#\.\.\.\.<br>\.\.#####<br>\.\.\.\.\.\.\.<br>\.\.\.H\.\.\.<br>5 7<br>Y\.\.\.\.P\.<br>\.\.#\.\.\.\.<br>\.\.#####<br>\.\.\.\.\.\.\.<br>\.\.\.H\.\.\.<br>2 3<br>\.YH<br>P## | YES<br>NO<br>NO |
{:.table_with_monospace_font}

**Εξήγηση 1<sup>ου</sup> σεναρίου**: Μια ασφαλής διαδρομή προς το σπίτι είναι η εξής: κάτω, κάτω, κάτω, δεξιά, δεξιά, δεξιά, κάτω. <u>Προσέξτε</u> ότι ο αστυνομικός δεν μπορεί να σας δώσει πρόστιμο στην αρχή αφού η απαγόρευση της κυκλοφορίας αρχίζει από το πρώτο λεπτό μετά τις 9.

**Εξήγηση 3<sup>ου</sup> σεναρίου**: <u>Προσέξτε</u> ότι για να μπείτε ασφαλείς στο σπίτι δεν πρέπει να σας βλέπει ο αστυνομικός.


## Περιορισμοί:

 * $$1 \leq T \leq 12$$<br>
 * $$1 \leq N, M \leq 700$$<br>
 * Για περιπτώσεις ελέγχου συνολικής αξίας 17%, ο χάρτης δεν θα έχει καθόλου κτίρια.<br>
 * Για περιπτώσεις ελέγχου συνολικής αξίας 42%, θα είναι $$1 \leq N, Μ \leq 200$$.<br>
 
## Προσοχή:

Φροντίστε να διαβάζετε την είσοδο και να εκτυπώνετε την έξοδο αποδοτικά, ειδικά αν προγραμματίζετε σε C++ ή Java.

**Μορφοποίηση**: Στην έξοδο, όλες οι γραμμές τερματίζουν με έναν χαρακτήρα newline.<br>
**Μέγιστος χρόνος εκτέλεσης**: $$1$$ sec.<br>
**Μέγιστη διαθέσιμη μνήμη**: $$64$$ MB.<br>