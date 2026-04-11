#include "Map.h"
#include "Search.h"
#include "ColorMap.h"
#include <cassert>
#include <iostream>

int main(int argc, char *argv[]){

    //Verify that the amount of arguments is correct
    //6 arguments: program name, map file, x1, y1, x2, y2
    if (argc!=6){
        std::cerr<<"Error: Cantidad de argumentos incorrecta."<<std::endl;
        std::cerr<<"Uso: "<<argv[0]<<" <map_file> <x1> <y1> <x2> <y2>"<<std::endl;
        return 1;
    }

    int start_x, start_y, goal_x, goal_y;
    try{
        start_x = std::stoi(argv[2]);
        start_y = std::stoi(argv[3]);
        goal_x = std::stoi(argv[4]);
        goal_y = std::stoi(argv[5]);
    } catch(const std::invalid_argument& e){
        std::cerr<<"Error: Argumentos de coordenadas deben ser enteros."<<std::endl;
        return 1;
    } catch(const std::out_of_range& e){
        std::cerr<<"Error: Argumentos de coordenadas fuera de rango."<<std::endl;
        return 1;
    }

    //Load map with class Map
    Map map(argv[1]);

    ColorMap colorMap(map);
    colorMap.print();

    //Check legal cordinates
    if (!map.isValidCordinates(start_x, start_y)){
        std::cerr<<"Error: Coordenadas de inicio no válidas."<<std::endl;
        return 1;
    }
    if (!map.isValidCordinates(goal_x, goal_y)){
        std::cerr<<"Error: Coordenadas de destino no válidas."<<std::endl;
        return 1;
    }

    auto path = Search::BFS(map, {start_x, start_y}, {goal_x, goal_y}); 
    
    std::cout << "\n-----------------------------------\n";
    std::cout << "Distancia del camino encontrado: " << (path.size() - 1) << " pasos." << std::endl;
    std::cout << "-----------------------------------\n\n";

    std::cout << "Mapa con la ruta encontrada:\n";
    colorMap.print(path);
    
    return 0;
}