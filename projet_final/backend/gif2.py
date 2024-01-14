import os
from PIL import Image

def extract_number(filename):
    # Utilisez '0' comme valeur par défaut si aucun chiffre n'est trouvé
    numbers = ''.join(filter(str.isdigit, filename))
    return int(numbers) if numbers else 0

def create_gif_from_folder(folder_path, gif_path, duration=500, loop=0):
    images = []

    # Parcours des fichiers dans le dossier
    for filename in sorted(os.listdir(folder_path), key=extract_number):
        if filename.endswith(".png"):
            img_path = os.path.join(folder_path, filename)
            img = Image.open(img_path)
            images.append(img)

    # Enregistrez les images sous forme de GIF
    images[0].save(
        gif_path,
        save_all=True,
        append_images=images[1:],
        duration=duration,
        loop=loop
    )

if __name__ == "__main__":
    # Chemin d'accès au dossier contenant les images PNG
    folder_path = "https://github.com/Art-Hashani/Projet_info_rendu_final/blob/c2df7684f548a7520a6034ff451ee502b10d060d/"

    # Chemin d'accès pour le fichier GIF de sortie
    gif_output_path = "https://github.com/Art-Hashani/Projet_info_rendu_final/blob/c2df7684f548a7520a6034ff451ee502b10d060d/output.gif"


    # Durée de chaque image en millisecondes (500 par défaut)
    frame_duration = 1000

    # Nombre de boucles (0 pour une boucle infinie)
    loop_count = 0

    # Créez le GIF à partir des images du dossier
    create_gif_from_folder(folder_path, gif_output_path, duration=frame_duration, loop=loop_count)

    print(f"Le GIF a été créé avec succès à {gif_output_path}")