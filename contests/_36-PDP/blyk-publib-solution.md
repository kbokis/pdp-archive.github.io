---
layout: statement
codename: publib
---

## Επεξήγηση εκφώνησης

Μας δίνεται ένας μη-κατευθυνόμενος γράφος και μας ζητείται να βρούμε την [ακτίνα](https://el.wikipedia.org/wiki/%CE%91%CE%BA%CF%84%CE%AF%CE%BD%CE%B1_(%CE%B8%CE%B5%CF%89%CF%81%CE%AF%CE%B1_%CE%B3%CF%81%CE%AC%CF%86%CF%89%CE%BD)) του γράφου.

<img style="float: right" src="/assets/36-bgym-publib.png"/>

Στο παράδειγμα της εκφώνησης, ο κόμβος $$1$$ απέχει $$2$$ από τον κόμβο $$2$$, απέχει $$2$$ από τον κόμβο $$3$$, απέχει $$3$$ από τον κόμβο $$4$$, κ.ο.κ. Συνοψίζοντας μπορούμε να βάλουμε τις αποστάσεις στην παρακάτω γραμμή:

<center>
<table style="width: auto; cellpadding: 1px">
<tr style="background:#e0e0e0"> <td style="padding: 3px">1</td> <td style="padding: 3px">2</td> <td style="padding: 3px">3</td> <td style="padding: 3px">4</td> <td style="padding: 3px">5</td> <td style="padding: 3px">6</td> <td style="padding: 3px">7</td> <td style="padding: 3px">8</td> </tr>
<tr><td style="padding: 3px">0</td> <td style="padding: 3px">2</td> <td style="padding: 3px">2</td> <td style="padding: 3px">3</td> <td style="padding: 3px">1</td> <td style="padding: 3px">2</td> <td style="padding: 3px">1</td> <td style="padding: 3px">1</td> </tr>
</table>
</center>

Παρατηρήστε ότι η μέγιστη απόσταση από τον κόμβο $$1$$ είναι προς τον κόμβο $$4$$. Επαναλαμβάνοντας για τους υπόλοιπους κόμβους, έχουμε

<center>
<table style="width: auto; cellpadding: 1px">
<tr style="background:#e0e0e0"> <td style="padding: 3px"></td> <td style="padding: 3px">1</td> <td style="padding: 3px">2</td> <td style="padding: 3px">3</td> <td style="padding: 3px">4</td> <td style="padding: 3px">5</td> <td style="padding: 3px">6</td> <td style="padding: 3px">7</td> <td style="padding: 3px">8</td> </tr>
<tr><td style="background:#e0e0e0">1</td> <td style="padding: 3px">0</td> <td style="padding: 3px">2</td> <td style="padding: 3px">2</td> <td style="padding: 3px"><b style="color:red">3</b></td> <td style="padding: 3px">1</td> <td style="padding: 3px">2</td> <td style="padding: 3px">1</td> <td style="padding: 3px">1</td> </tr>
<tr><td style="background:#e0e0e0">2</td> <td style="padding: 3px">2</td> <td style="padding: 3px">0</td> <td style="padding: 3px"><b>4</b></td> <td style="padding: 3px">1</td> <td style="padding: 3px">1</td> <td style="padding: 3px">2</td> <td style="padding: 3px">3</td> <td style="padding: 3px">1</td> </tr>
<tr><td style="background:#e0e0e0">3</td> <td style="padding: 3px">2</td> <td style="padding: 3px">4</td> <td style="padding: 3px">0</td> <td style="padding: 3px"><b>5</b></td> <td style="padding: 3px">3</td> <td style="padding: 3px">4</td> <td style="padding: 3px">1</td> <td style="padding: 3px">3</td> </tr>
<tr><td style="background:#e0e0e0">4</td> <td style="padding: 3px">3</td> <td style="padding: 3px">1</td> <td style="padding: 3px"><b>5</b></td> <td style="padding: 3px">0</td> <td style="padding: 3px">2</td> <td style="padding: 3px">1</td> <td style="padding: 3px">4</td> <td style="padding: 3px">2</td> </tr>
<tr><td style="background:#e0e0e0">5</td> <td style="padding: 3px">1</td> <td style="padding: 3px">1</td> <td style="padding: 3px"><b style="color:red">3</b></td> <td style="padding: 3px">2</td> <td style="padding: 3px">0</td> <td style="padding: 3px"><b style="color:red">3</b></td> <td style="padding: 3px">2</td> <td style="padding: 3px">2</td> </tr>
<tr><td style="background:#e0e0e0">6</td> <td style="padding: 3px">2</td> <td style="padding: 3px">2</td> <td style="padding: 3px"><b>4</b></td> <td style="padding: 3px">1</td> <td style="padding: 3px">3</td> <td style="padding: 3px">0</td> <td style="padding: 3px">3</td> <td style="padding: 3px">1</td> </tr>
<tr><td style="background:#e0e0e0">7</td> <td style="padding: 3px">1</td> <td style="padding: 3px">3</td> <td style="padding: 3px">1</td> <td style="padding: 3px"><b>4</b></td> <td style="padding: 3px">2</td> <td style="padding: 3px">3</td> <td style="padding: 3px">0</td> <td style="padding: 3px">2</td> </tr>
<tr><td style="background:#e0e0e0">8</td> <td style="padding: 3px">1</td> <td style="padding: 3px">1</td> <td style="padding: 3px"><b style="color:red">3</b></td> <td style="padding: 3px">2</td> <td style="padding: 3px">2</td> <td style="padding: 3px">1</td> <td style="padding: 3px">2</td> <td style="padding: 3px">0</td> </tr>
</table>
</center>

όπου με **έντονα γράμματα** αποτυπώνεται η μέγιστη απόσταση για κάθε κόμβο. Η μικρότερη από αυτές είναι η απάντηση, δηλαδή η ακτίνα του γράφου, και δίνεται με κόκκινο. Υπάρχουν τρεις κόμβοι που πετυχαίνουν αυτή την ελάχιστη απόσταση, ο $$1$$, ο $$5$$ και ο $$8$$.

## Βέλτιστη λύση

Σε έναν μη-κατευθυνόμενο γράφο όπου οι ακμές δεν έχουν βάρη μπορούμε να βρούμε την συντομότερη απόσταση από έναν κόμβο $$u$$ προς όλους τους άλλους χρησιμοποιώντας την *αναζήτηση κατά πλάτος* (ή αλλιώς BFS). Ο τρόπος που δουλεύει ο αλγόριθμος είναι ο εξής: 
 - Ξεκινάμε με μία ουρά (queue) που αρχικά έχει τον κόμβο $$u$$ (με απόσταση $$0$$)
 - Κατόπιν επαναλαμβάνουμε όσο η ουρά δεν έχει αδειάσει:
   - Αφαιρούμε κάθε κόμβο και την απόσταση του $$d$$ από την ουρά, και προσθέτουμε στο τέλος της ουράς με απόσταση $$d+1$$, τους γείτονες του που δεν έχουμε ήδη συναντήσει.

Ο τελευταίος κόμβος που προσθέτουμε έχει τη μέγιστη απόσταση από τον κόμβο $$u$$. Επομένως, επαναλαμβάνουμε την αναζήτηση κατά πλάτος μία φορά από κάθε κόμβο, και η ελάχιστη μέγιστη απόσταση είναι η ακτίνα του γράφου. Ο παρακάτω κώδικας υλοποιεί ακριβώς αυτό. 

{% include code.md solution_name='publib_bfs_with_queue.cc' start=25 end=46 %}

Παρακάτω δίνεται ένα παράδειγμα εκτέλεσης της αναζήτησης κατά πλάτος για τον κόμβο $$u = 1$$, όπου η ουρά $$q$$ κρατάει τα ζεύγη κόμβου και απόστασης:
<center>
<img width=600px src="/assets/36-blyk-publib-bfs_example.svg"/>
</center>

Κάθε αναζήτηση κατά πλάτος θέλει $$\mathcal{O}(M)$$ χρόνο, επομένως συνολικά ο αλγόριθμος χρειάζεται $$O(N \cdot M)$$ χρόνο. Μπορείτε να βρείτε ολόκληρο τον κώδικα [εδώ]({% include link_to_source.md solution_name='publib_bfs_with_queue.cc' %}).

**Εναλλακτικές υλοποιήσεις:** Η ουρά μπορεί να υλοποιηθεί με την χρήση ενός πίνακα, που ενώ έχει την ίδια πολυπλοκότητα, στην πράξη είναι λίγο πιο γρήγορη γιατί αποφεύγει τις πολλές δεσμεύσεις μνήμης (δείτε [εδώ]({% include link_to_source.md solution_name='publib_bfs_with_array_queue.cc' %}) τον κώδικα). Επίσης, η αναζήτηση κατά πλάτος, μπορεί να υλοποιηθεί με δύο πίνακες ακεραίων αντί για μία ουρά με ζεύγη (δείτε [εδώ]({% include link_to_source.md solution_name='publib_bfs.cc' %}) τον κώδικα).
