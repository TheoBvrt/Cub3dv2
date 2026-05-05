#!/bin/bash

# Vérifie si un dossier est passé en argument, sinon utilise le dossier courant
TARGET_DIR=${1:-.}

# Boucle sur tous les fichiers du dossier
for file in "$TARGET_DIR"/maps/good/*; do
    # Vérifie si c'est bien un fichier (évite les dossiers)
    if [ -f "$file" ]; then
        echo "Exécution de ./cub3D sur $file..."
        valgrind --leak-check=full -s ./cub3D "$file"
    fi
done