#include "GameState.h"
#include"conmanip.h"
#define _WIN32_WINNT 0x0500

using namespace conmanip;

using namespace std;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int read_input()
{
    int input = -1;
    bool valid= false;
    do
    {
        cin >> input;
        if (cin.good())
        {
            valid = true;
        }
        else
        {
            cin.clear();
            //and empty it
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Opcion invalida porfavor reingrese la opcion." << endl;
        }
    } while (!valid);

    return (input);
}

void PunjaePartida(int puntaje){

        if(puntaje <= 45 && puntaje > 0){
cout<< R"(
       __                                                __           __
      / /_  _____  ____ _____     ________  ____ ___  __/ /___ ______/ /
 __  / / / / / _ \/ __ `/ __ \   / ___/ _ \/ __ `/ / / / / __ `/ ___/ /
/ /_/ / /_/ /  __/ /_/ / /_/ /  / /  /  __/ /_/ / /_/ / / /_/ / /  /_/
\____/\__,_/\___/\__, /\____/  /_/   \___/\__, /\__,_/_/\__,_/_/  (_)
                /____/                   /____/
)"<<'\n';
system("pause");
        }
        else if(puntaje <= 0){
cout<< R"(
       __                                          ____          __        __
      / /_  _____  ____ _____     ____  ___  _____/ __/__  _____/ /_____  / /
 __  / / / / / _ \/ __ `/ __ \   / __ \/ _ \/ ___/ /_/ _ \/ ___/ __/ __ \/ /
/ /_/ / /_/ /  __/ /_/ / /_/ /  / /_/ /  __/ /  / __/  __/ /__/ /_/ /_/ /_/
\____/\__,_/\___/\__, /\____/  / .___/\___/_/  /_/  \___/\___/\__/\____(_)
                /____/        /_/
)"<<'\n';
system("pause");
        }
    else{

cout<< R"(
    ____              __          _                                        ____
   / __ \__  ______  / /_____ _  (_)__     ____ ___  __  ____  __   ____ _/ / /_____
  / /_/ / / / / __ \/ __/ __ `/ / / _ \   / __ `__ \/ / / / / / /  / __ `/ / __/ __ \
 / ____/ /_/ / / / / /_/ /_/ / / /  __/  / / / / / / /_/ / /_/ /  / /_/ / / /_/ /_/ /
/_/    \__,_/_/ /_/\__/\__,_/_/ /\___/  /_/ /_/ /_/\__,_/\__, /   \__,_/_/\__/\____/
                           /___/                        /____/
)"<<'\n';
system("pause");

    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
   // Aqui vamos a configurar la consola de salida para que tenga un tamano optimo para el funcionamiento del juego

   console_out_context ctxout;
   console_out conout(ctxout);
    conout.settitle("Retro Solitaire Collection");
    SetConsoleOutputCP(65001);
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MoveWindow(console, r.left, r.top, 1080, 800, TRUE); // La resolucion que vamos a utilizar para el optimo funcionamiento es de 1080 * 800   900*700

    GameState gs;
    SolitarioS gs1;

    //gs.playSpiderSolitaire();
    //system("cls");

        cout<< R"(
                           ___ __        _                         ____          __  _
               _________  / (_) /_____ _(_)_______     _________  / / /__  _____/ /_(_)___  ____
              / ___/ __ \/ / / __/ __ `/ / ___/ _ \   / ___/ __ \/ / / _ \/ ___/ __/ / __ \/ __ \
             (__  ) /_/ / / / /_/ /_/ / / /  /  __/  / /__/ /_/ / / /  __/ /__/ /_/ / /_/ / / / /
            /____/\____/_/_/\__/\__,_/_/_/   \___/   \___/\____/_/_/\___/\___/\__/_/\____/_/ /_/

)"<<'\n';
cout<<"--------------------------------------------------------------------------------------------------------"<<endl;
cout<<"Golf Solitaire                                                                                        1"<<endl;
cout<<"Spider Solitaire                                                                                      2"<<endl;
int opc = 0;
opc=read_input();
switch(opc){

case 1:
    do{
    cout<<"Para jugar las nueve rondas presione 1, si desea jugar solo una ronda presione 0"<<endl;
    cout<<"Si desea salir presione cualquier otro numero"<<endl;
    opc=read_input();
    if (opc == 1){
        for(int i=0; i<9;i++){
            system("cls");
            ShowConsoleCursor(false);
            gs.playGolfSolitaire();
            system("cls");
            cout<<"El puntaje acumulado en la ronda "<<i+1<<" es de: "<<gs.getPuntajeGolf()<<endl;
            system("pause");
        }
        PunjaePartida(gs.getPuntajeGolf());
    }
    else if (opc == 0){
        system("cls");
        ShowConsoleCursor(false);
        gs.playGolfSolitaire();
        system("cls");
        PunjaePartida(gs.getPuntajeGolf());
    }
    else{
        cout<<"Esta opcion no es valida!"<<endl;
    }
    }while((opc != 1) && (opc != 0));
    break;

case 2:

    system("cls");
    gs1.jugar();
    break;

}
system("cls");

        cout<< R"(
   _____                _                                  _                        _
  / ____|              (_)                                (_)                      | |
 | |  __ _ __ __ _  ___ _  __ _ ___   _ __   ___  _ __     _ _   _  __ _  __ _ _ __| |
 | | |_ | '__/ _` |/ __| |/ _` / __| | '_ \ / _ \| '__|   | | | | |/ _` |/ _` | '__| |
 | |__| | | | (_| | (__| | (_| \__ \ | |_) | (_) | |      | | |_| | (_| | (_| | |  |_|
  \_____|_|  \__,_|\___|_|\__,_|___/ | .__/ \___/|_|      | |\__,_|\__, |\__,_|_|  (_)
                                     | |                 _/ |       __/ |
                                     |_|                |__/       |___/
)"<<'\n';

system("pause");
    return 0;
}


