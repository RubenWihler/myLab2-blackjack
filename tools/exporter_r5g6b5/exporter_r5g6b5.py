from PIL import Image
import sys
import os
import textwrap

def bmp_to_c_header(input_path, output_path, var_name):
    # Ouvre l'image
    img = Image.open(input_path)

    # Vérifie que l'image est en mode RGB565 (mode "RGB;16" depuis Pillow >=10.0.0)
    # On convertit en mode 'RGB' si nécessaire, mais l'idée ici est que l'image est déjà bien encodée
    img = img.convert('RGB')

    width, height = img.size
    pixels = img.load()

    if pixels is None:
        return

    # Liste des octets (chaînes échappées)
    raw_bytes = []

    #format octal C
    for y in range(height):
        for x in range(width):
            r, g, b = pixels[x, y]
            rgb565 = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)
            raw_bytes.append(f"\\{((rgb565 >> 8) & 0xFF):03o}")  # MSB
            raw_bytes.append(f"\\{(rgb565 & 0xFF):03o}")         # LSB

    # Regroupe en lignes de 36 octets (72 caractères échappés)
    lines = textwrap.wrap("".join(raw_bytes), 72)

    # Écrit le fichier .h
    with open(output_path, "w") as f:
        f.write(f"// Generated from {os.path.basename(input_path)}\n")
        f.write("#pragma once\n")
        f.write("#include \"../../liblcp/rendering/sprite/sprite_renderer.h\"\n\n")

        f.write("typedef unsigned char uint8_t;\n\n")
        f.write(f"static const uint8_t __{var_name.lower()}_data__[{width} * {height} * 2] = {{\n")
        for line in lines:
            f.write(f'    "{line}"\n')
        f.write("};\n")
        f.write(f"const sprite_t {var_name} = " + "{\n")
        f.write(f"    .width = {width},\n")
        f.write(f"    .height = {height},\n")
        f.write(f"    .data = (uint8_t*)__{var_name.lower()}_data__\n")
        f.write("};\n")

    print(f"exportation reussi : {output_path}")

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage : python bmp_to_header.py <sprite name> <image.bmp> <output.h>")
    else:
        bmp_to_c_header(sys.argv[2], sys.argv[3], sys.argv[1])

