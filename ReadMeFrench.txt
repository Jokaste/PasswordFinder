Vous pouvez utiliser librement PasswordFinder, mais il ne doit pas servir à autre chose qu'à des fins éducatives.
Voilà, j'ai sauvé la face. J'ai mis le texte qui va me protégér. L'honneur est sauf, même si tout cela c'est du bidon.

PasswordFinder est écrit en langage 'C'. Il est proposé en freeware. That's all.

Il ne saurait remplacer des outils aussi puissants que John The Ripper, Caïn et Abel... Mais c'est un outil de plus.

PasswordFinder est un outil permettant de générer des clefs de hashage en fonctions de mots de passe.
Il dispose de plusieurs alphabets. Il est capable de générer des mots de passe de longueur 1 à 16 caractères.
Il permet d'importer des listes de mots de passe ou de rechercher un mot de passe en fournissant sa clef de hachage.
Ne croyez pas pouvoir hacker n'importe qui et n'importe quoi avec ce programme. Il vous faut disposer de clefs de hashage.

Pour y arriver il a fallu récupérer ces clefs chez un utilisateur. Il y a plusieurs façons de les récupérer.

1 - Installer un keylogger, Virus, qui transférera automatiquement les frappes au clavier.
2 - Au cours d'une session internet se positionner entre l'utilisateur et les sites qu'il visite (Man in the Middle).
3 - A l'aide d'un outil comme WireShark, capturer la session de l'utilisateur.
4 - Faire venir l'utilisateur sur votre site internet et lui proposer de tester la force de ses mots de passe.
5 - Faire venir l'utilisateur, Phishing, et lui demander de changer ses mots de passe.

La liste ne saurait être exhaustive, mais sert à la compréhénsion.

PasswordFinder enregistre ses données dans des tables SQLite accessibles par n'importe quel logiciel de base de données.

Les algorithmes de PasswordFinder :
----------------------------------- 

  1 - Abacus (128 bits)
  2 - Abacus (160 bits)
  3 - Abacus (192 bits)
  4 - Abacus (224 bits)
  5 - Abacus (256 bits)
  6 - Abacus (384 bits)
  7 - Abacus (512 bits)
  8 - Abacus (1024 bits)
  9 - AriRang (224 bits)
 10 - AriRang (256 bits)
 11 - AriRang (384 bits)
 12 - AriRang (512 bits)
 13 - Aurora (224 bits)
 14 - Aurora (256 bits)
 15 - Aurora (384 bits)
 16 - Aurora (512 bits)
 17 - Blake (224 bits)
 18 - Blake (256 bits)
 19 - Blake (384 bits)
 20 - Blake (512 bits)
 21 - Blender (192 bits)
 22 - Blender (224 bits)
 23 - Blender (256 bits)
 24 - Blender (288 bits)
 25 - Blender (320 bits)
 26 - Blender (384 bits)
 27 - Blender (448 bits)
 28 - Blender (512 bits)
 29 - Blender (576 bits)
 30 - Blender (640 bits)
 31 - Bmw (224 bits)
 32 - Bmw (256 bits)
 33 - Bmw (384 bits)
 34 - Bmw (512 bits)
 35 - Boole (224 bits)
 36 - Boole (256 bits)
 37 - Boole (384 bits)
 38 - Boole (512 bits)
 39 - Cheetah (224 bits)
 40 - Cheetah (256 bits)
 41 - Cheetah (384 bits)
 42 - Cheetah (512 bits)
 43 - Crunch (224 bits)
 44 - Crunch (256 bits)
 45 - Crunch (384 bits)
 46 - Crunch (512 bits)
 47 - CubeHash (224 bits)
 48 - CubeHash (256 bits)
 49 - CubeHash (384 bits)
 50 - CubeHash (512 bits)
 51 - Echo (224 bits)
 52 - Echo (256 bits)
 53 - Echo (384 bits)
 54 - Echo (512 bits)
 55 - Fugue (224 bits)
 56 - Fugue (256 bits)
 57 - Fugue (384 bits)
 58 - Fugue (512 bits)
 59 - Grøstl (224 bits)
 60 - Grøstl (256 bits)
 61 - Grøstl (384 bits)
 62 - Grøstl (512 bits)
 63 - Hamsi (224 bits)
 64 - Hamsi (256 bits)
 65 - Hamsi (384 bits)
 66 - Hamsi (512 bits)
 67 - Haval_3 (128 bits)
 68 - Haval_3 (160 bits)
 69 - Haval_3 (192 bits)
 70 - Haval_3 (224 bits)
 71 - Haval_3 (256 bits)
 72 - Haval_4 (128 bits)
 73 - Haval_4 (160 bits)
 74 - Haval_4 (192 bits)
 75 - Haval_4 (224 bits)
 76 - Haval_4 (256 bits)
 77 - Haval_5 (128 bits)
 78 - Haval_5 (160 bits)
 79 - Haval_5 (192 bits)
 80 - Haval_5 (224 bits)
 81 - Haval_5 (256 bits)
 82 - Jh (224 bits)
 83 - Jh (256 bits)
 84 - Jh (384 bits)
 85 - Jh (512 bits)
 86 - Keccak (224 bits)
 87 - Keccak (256 bits)
 88 - Keccak (384 bits)
 89 - Keccak (512 bits)
 90 - Luffa (224 bits)
 91 - Luffa (256 bits)
 92 - Luffa (384 bits)
 93 - Luffa (512 bits)
 94 - Maraca (128 bits)
 95 - Md 2 (128 bits)
 96 - Md 4 (128 bits)
 97 - Md 5 (128 bits)
 98 - Md 5(Sha1) (128 bits)
 99 - Md 6 (128 bits)
100 - Md 6 (160 bits)
101 - Md 6 (192 bits)
102 - Md 6 (224 bits)
103 - Md 6 (256 bits)
104 - Md 6 (384 bits)
105 - Md 6 (512 bits)
106 - Panama (256 bits)
107 - RadioGatun (256 bits)
108 - RadioGatun (64 bits)
109 - RipeMd (128 bits)
110 - RipeMd (160 bits)
111 - Sarmal (224 bits)
112 - Sarmal (256 bits)
113 - Sarmal (384 bits)
114 - Sarmal (512 bits)
115 - Sha 0 (160 bits)
116 - Sha 1 (160 bits)
117 - Sha 1(Md 5) (160 bits)
118 - Sha 1(Sha1) (160 bits)
119 - Sha 2 (224 bits)
120 - Sha 2 (256 bits)
121 - Sha 2 (384 bits)
122 - Sha 2 (512 bits)
123 - Shabal (192 bits)
124 - Shabal (224 bits)
125 - Shabal (256 bits)
126 - Shabal (384 bits)
127 - Shabal (512 bits)
128 - Shamata (224 bits)
129 - Shamata (256 bits)
130 - Shamata (384 bits)
131 - Shamata (512 bits)
132 - Shavite (224 bits)
133 - Shavite (256 bits)
134 - Shavite (384 bits)
135 - Shavite (512 bits)
136 - Simd (224 bits)
137 - Simd (256 bits)
138 - Simd (384 bits)
139 - Simd (512 bits)
140 - Skein (224 bits)
141 - Skein (256 bits)
142 - Skein (384 bits)
143 - Skein (512 bits)
144 - Stream Hash (224 bits)
145 - Stream Hash (256 bits)
146 - Stream Hash (384 bits)
147 - Stream Hash (512 bits)
148 - Tiger (192 bits)
149 - Waterfall (512 bits)
150 - Whirlpool (512 bits)

Quelques alphabets de PasswordFinder :
--------------------------------------

 " !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "+-*/%"
 "-."
 "01 !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "01"
 "01+-*/%"
 "01-."
 "0123456789 !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "0123456789"
 "0123456789+-*/%"
 "0123456789-."
 "ABCDEFGHIJKLMNOPQRSTUVWXYZ !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZ-."
 "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-*/%"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-."
 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-*/%"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-."
 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-*/%"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-."
 "AEIOUY !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "AEIOUY"
 "AEIOUY+-*/%"
 "AEIOUY-."
 "AEIOUY01 !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "AEIOUY01"
 "AEIOUY01+-*/%"
 "AEIOUY01-."
 "AEIOUYaeiouy !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "AEIOUYaeiouy"
 "AEIOUYaeiouy+-*/%"
 "AEIOUYaeiouy-."
 "AEIOUYaeiouy01 !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "AEIOUYaeiouy01"
 "AEIOUYaeiouy01+-*/%"
 "AEIOUYaeiouy01-."
 "BCDFGHJKLMNPQRSTVWXZ !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "BCDFGHJKLMNPQRSTVWXZ"
 "BCDFGHJKLMNPQRSTVWXZ+-*/%"
 "BCDFGHJKLMNPQRSTVWXZ-."
 "BCDFGHJKLMNPQRSTVWXZ01 !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "BCDFGHJKLMNPQRSTVWXZ01"
 "BCDFGHJKLMNPQRSTVWXZ01+-*/%"
 "BCDFGHJKLMNPQRSTVWXZ01-."
 "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz"
 "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz+-*/%"
 "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz-."
 "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz01 !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz01"
 "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz01+-*/%"
 "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz01-."
 "abcdefghijklmnopqrstuvwxyz !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "abcdefghijklmnopqrstuvwxyz"
 "abcdefghijklmnopqrstuvwxyz+-*/%"
 "abcdefghijklmnopqrstuvwxyz-."
 "abcdefghijklmnopqrstuvwxyz0123456789 !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "abcdefghijklmnopqrstuvwxyz0123456789"
 "abcdefghijklmnopqrstuvwxyz0123456789+-*/%"
 "abcdefghijklmnopqrstuvwxyz0123456789-."
 "aeiouy !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "aeiouy"
 "aeiouy+-*/%"
 "aeiouy-."
 "aeiouy01 !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "aeiouy01"
 "aeiouy01+-*/%"
 "aeiouy01-."
 "bcdfghjklmnpqrstvwxz !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "bcdfghjklmnpqrstvwxz"
 "bcdfghjklmnpqrstvwxz+-*/%"
 "bcdfghjklmnpqrstvwxz-."
 "bcdfghjklmnpqrstvwxz01 !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~£¤§¨°²µ€"
 "bcdfghjklmnpqrstvwxz01"
 "bcdfghjklmnpqrstvwxz01+-*/%"
 "bcdfghjklmnpqrstvwxz01-."

Les fonctions de PasswordFinder :
---------------------------------

1 - Générer automatiquement des mots de passe de 1 à 16 caractères de long. Pendant la génération, des points de reprise
sont créés. Il est donc possible de stopper une génération à tous moments.

2 - Importer une liste de mots de passe. Le fichier d'importation doit être au format texte et doit comporter un mot de passe
par ligne. Le fichier peut avoir l'extension txt ou csv, cela importe peu. Les lignes doivent être séparées par un 
CRLF (Carriage Return & Line Feed), format Windows et non par un LF (Line Feed) format pingouin. Les fichiers doivent être encodés au format ANSI.

3 - Insérer manuellement un mot de passe.

4 - Rechercher un mot de passe en fournissant la clef de hashage.

Autres :
--------

Pour certaines opérations, il y a deux modes de fonctionnement :

1 - Le mode "Background" : Les opérations s'effectuent en arrière plan permettant ainsi d'utiliser l'ordinateur sans
être trop pénalisé.

2 - Le mode "Foreground" : Les opérations s'effectuent en avant plan, rendant l'utilisation d'autres logiciels plus lentes.
Cela à quand même l'avantage de rendre PasswordFinder plus rapide, c'est le principal.

Dans les premières versions du logiciel, je stockais 16 000 000 de mots de passe par table, ce qui en soit consistait
à un exploit. Allier vitesse et stockage avec SQLITE me semblait une prouesse.
Mais c'était sans compter sur le revers de la médaille, lors SQLite réorganissait les tables, commandes "VACUUM",
cela était très très long.

L'autre inconvénient, plus gênant celui-là, empêchait une recherche de mot de passe à travers des fichiers.
J'ai donc réduit le nombre de mots de passe stockés à 500 000. Bien évidemment, les tables sont beaucoup plus nombreuses,
mais les recherches s'en trouvent grandement améliorées.

Parfois, il est utile de combiner plusieurs alphabets pour générer des mots de passe. Le nouvel alphabet est donc composé
de deux sous-ensembles. Exemple : Lettres minuscules et Nombres.

Le principal inconvénient de cet alphabet est qu'il génère trop de combinaisons. Imaginons que les combinaisons de nombres
ont été déjà créées. Idem pour les lettres minuscules.

Donc le nouvel alphabet va créer trois types de combinaisons :

	1 - Les lettres minuscules
	2 - Les nombres
	3 - Les lettres minuscules et les nombres

J'ai inclu une nouvelle règle : Quand un alphabet est composé de sous-ensembles, le programme ne génère ques les combinaisons
portant sur tous les sous-ensembles en même temps. Dans l'exemple plus haut, le programme éliminera les points 1 et 2 pour ne
garder que le point 3.

Il y a maintenant 375 alphabets représentants toutes les combinaisons possibles d'alphabets.

Dans ces alphabets vous ne retrouverez pas :

	Nombres & Binaire
	Signes & Opérateurs
	Signes & Morse
	Lettres minuscules & voyelles minuscules
	Lettres majuscules & voyelles majuscules
	Lettres minuscules & consonnes minuscules
	Lettres majuscules & consonnes majuscues

La aussi, une nouvelle règle a été introduite : Quand un alphabet est inclu dans un autre plus grand, on ne le crée pas.
