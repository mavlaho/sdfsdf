# OAA Seminar

* U <code>doc</code> folderu nalazi se prezentacija.
* U <code>src</code> folderu nalazi se kod.
* Potrebno je imati instaliran <code>g++</code> compiler.
* Kod se pokreće tako da udjemo u terminal, navigiramo u folder u kojem je smjestem <code>Makefile</code>.
Upisemo naredbu <code>make</code> što će prevesti program te kreirati izvršnu datoteku <code>run</code>.
Kod pokrećemo naredboj <code>./run [NumberOfExperiments]</code>, npr. <code>./run 100</code>.
* Ta će naredba izvšiti program napisan u <code>./src/main.cpp</code>, te usporediti Radix sort sa
<code>std::sort</code>, onoliko puta koliko smo unjeli kao argument komandne linije <code>[NumberOfExperiments]</code>.

