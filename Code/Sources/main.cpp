#include "../Headers/Editor.hpp"
#include "../Headers/Image.hpp"

#include <iostream>
//#include <windows.h>

#include "../Headers/Files.hpp"
#include "../Headers/Picker.hpp"

int main(int argc,char* argv[]) {

    //_setmode(_fileno(stdout), 0x00020000);

    Editor editor;
    if (argc > 1 && ExistingFile(argv[1])) {
        
        editor.Open(argv[1]);
    
    } else {

        if (argc > 1) { 

            std::cout << "ERREUR: Chargement du fichier : \n" << argv[1] << "\nce fichier n'existe pas ou possede des caracteres speciaux !\n\nchargement de \"unamed.ppm\"...";
            std::cin.ignore();
            std::system("cls");

        }

        editor.New();

    }

    while (Editor::start) {
        
        editor.Update();
        editor.Render();

        
    }

    return 0;

}