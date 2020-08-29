# KAD 

## Information
Ce projet a ete realise dans le cadre de la 1er anne en ecole d'inegneire a telecom nancy . 
Ce projet fut relir par Vincent Lambert de Curset , Bocar NIANG et max clerc 
## Installation:
### Prérequis:

-   Linux : https://www.linux.org/
    
-   openSSL : 	`sudo apt-get install openssl-dev`
 			[https://github.com/openssl/openssl](https://github.com/openssl/openssl)

- mpg123  **Optionel**: `sudo apt-get install mpg123`
http://mpg123.org/

  

### Building:

`make`

ou

`make music`: La compilation pouvant prendre un peu de temps nous vous proposons d'utiliser cette commande (après installation de mpg123)

ou

`Cmake .`

## Utilisation:

Lancer le programme avec `./kad` 

Le programme prend en entrée plusieurs options :

**-p** : port du pair qui servira à l'entrée dans le réseau

**-i** : ip de du pair qui servira à entrer dans le réseau

**-q** : port utilisé par l'application

**-m** : ip utilisé par l'application

**-s** : id de l'application (si vous voulez utiliser la même ID )
 
Il est important qu'au lancement de l'application vous indiquiez les coordonnées du nœud pour se connecter . Dans le cas contraire, votre application ne pourra pas communiquer avec le réseau sauf si elle est contactée par d’autre nœud .

  

Nous vous conseillons aussi d'indiquer le port utilisé par l'application afin de faciliter la création du réseau . Dans le cas où vous n'indiquez pas le port, ce dernier est choisi automatiquement (il vous sera affiché dans la console)

### Commande:

  

Une fois l’application correctement lancée vous pouvez interagir avec l'application à travers des commandes suivantes :

`add <add path/to/file.ext>`  Cela ajoute un fichier au réseau

`find  <find file.ext>` cherche le fichier sur le réseau . Si ce dernier est trouvé il le télécharge. exit : quitte le programme

  

Tous les fichiers téléchargés et la base de données seront créés depuis l'endroit où vous lance le fichier dans `nodespace/id/`

  

**ex :** `nodespace/042ac-547438-01234-5678-95187`

**Pour créer un réseau :**

1. Lancer une première fois kad avec un port connus, ce noeud sera notre point d'entrée du réseau . 
	**ex :** `./kad -q 8080 -m 127.0.0.1`

2.  ajout des node au réseau  `./kad -p 8080 -i 127.0.0.1`

## Disclaimer:  

Tout le programme a été testé sous linux , nous ne garantissons pas son bon fonctionnement sous Mac et Windows (Notamment pour les packets réseau) .

