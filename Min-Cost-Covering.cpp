#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> //atoi
using namespace std;

class Vertices {
public :
    int label;
    int predecessor_one ;
    int predecessor_two ;
    int type;  //not:1,nand:2
    bool have_gate;
    int cost;
};
Vertices gate[50];
int mincost(Vertices vertices);
int compare_pattern(Vertices vertices);

int mincost(Vertices vertices){
    int old_cost, new_cost;
    if(vertices.type == 1){  //not
        if(vertices.predecessor_one == -1){  //primary input
            gate[vertices.label].cost = 1;
            return 1;
        }else{
            if(gate[vertices.predecessor_one].cost == 1000){
                old_cost = mincost(gate[vertices.predecessor_one]) + 1;
            }else{
                old_cost = gate[vertices.predecessor_one].cost + 1;
            }
            new_cost = compare_pattern(vertices);
            if(new_cost == -1){
                gate[vertices.label].cost = old_cost;
                return  old_cost ;
            }else{
                if(new_cost < old_cost){
                    gate[vertices.label].cost = new_cost;
                    return  new_cost ;
                }else{
                    gate[vertices.label].cost = old_cost;
                    return  old_cost ;
                }
            }
        }
    }else if(vertices.type == 2){ //nand
        if(vertices.predecessor_one == -1 && vertices.predecessor_two == -1){  //primary input
            gate[vertices.label].cost = 2 ;
            return 2;
        }else if(vertices.predecessor_one == -1 && vertices.predecessor_two != -1){
            if(gate[vertices.predecessor_two].cost == 1000){
               old_cost = mincost(gate[vertices.predecessor_two]) + 2;
            }else{
                old_cost = gate[vertices.predecessor_two].cost + 2;
            }
            new_cost = compare_pattern(vertices);
            if(new_cost == -1){
                gate[vertices.label].cost = old_cost;
                return  old_cost ;
            }else{
                if(new_cost < old_cost){
                    gate[vertices.label].cost = new_cost;
                    return  new_cost ;
                }else{
                    gate[vertices.label].cost = old_cost;
                    return  old_cost ;
                }
            } 
        }else if(vertices.predecessor_one != -1 && vertices.predecessor_two == -1){
            if(gate[vertices.predecessor_one].cost == 1000){
                old_cost = mincost(gate[vertices.predecessor_one]) + 2;
            }else{
                old_cost = gate[vertices.predecessor_one].cost + 2;
            }
            new_cost = compare_pattern(vertices);
            if(new_cost == -1){
                gate[vertices.label].cost = old_cost;
                return  old_cost ;
            }else{
                if(new_cost < old_cost){
                    gate[vertices.label].cost = new_cost;
                    return  new_cost ;
                }else{
                    gate[vertices.label].cost = old_cost;
                    return  old_cost ;
                }
            } 
        }else{
            if(gate[vertices.predecessor_one].cost == 1000 && gate[vertices.predecessor_two].cost == 1000){
                old_cost = mincost(gate[vertices.predecessor_one]) + mincost(gate[vertices.predecessor_two])+ 2;
            }else if(gate[vertices.predecessor_one].cost == 1000 && gate[vertices.predecessor_two].cost != 1000){
                old_cost = mincost(gate[vertices.predecessor_one]) + gate[vertices.predecessor_two].cost + 2;
            }else if(gate[vertices.predecessor_one].cost != 1000 && gate[vertices.predecessor_two].cost == 1000){
                old_cost = gate[vertices.predecessor_one].cost + mincost(gate[vertices.predecessor_two]) + 2;
            }else{
                old_cost = gate[vertices.predecessor_one].cost + gate[vertices.predecessor_two].cost + 2;
            }
            new_cost = compare_pattern(vertices);
            if(new_cost == -1){
                gate[vertices.label].cost = old_cost;
                return  old_cost ;
            }else{
                if(new_cost < old_cost){
                    gate[vertices.label].cost = new_cost;
                    return  new_cost ;
                }else{
                    gate[vertices.label].cost = old_cost;
                    return  old_cost ;
                }
            } 
        }
    }else return 0;
}

int compare_pattern(Vertices vertices){
    Vertices temp, temp_one ,temp_two;
    int c1,c2,c3,c4, min[4], min_r;
    if (vertices.type == 1){  //not
        temp = gate[vertices.predecessor_one];
        if(temp.type == 1){   // buf
           if(temp.predecessor_one == -1){ 
                return 0;
           }else{  
                return gate[temp.predecessor_one].cost + 0;
           }
        }else if(temp.type == 2){
           if(temp.predecessor_one == -1 || temp.predecessor_two == -1){ 
                return -1;
           }else{                         
                temp_one = gate[temp.predecessor_one];
                temp_two = gate[temp.predecessor_two];
                if(temp_one.type == 1 && temp_two.type == 2){ //aoi21
                    if(temp_one.predecessor_one == -1) c1 = 0;
                    else c1 = gate[temp_one.predecessor_one].cost;
                    if(temp_two.predecessor_one == -1) c2 = 0;
                    else c2 = gate[temp_two.predecessor_one].cost;
                    if(temp_two.predecessor_two == -1) c3 = 0;
                    else c3 = gate[temp_two.predecessor_two].cost;
                    return c1 + c2 + c3 + 3;
                }else if(temp_one.type == 2 && temp_two.type == 1){ //aoi21
                    if(temp_one.predecessor_one == -1) c1 = 0;
                    else c1 = gate[temp_one.predecessor_one].cost;
                    if(temp_one.predecessor_two == -1) c2 = 0;
                    else c2 = gate[temp_one.predecessor_two].cost;
                    if(temp_two.predecessor_one == -1) c3 = 0;
                    else c3 = gate[temp_two.predecessor_one].cost;
                    return c1 + c2 + c3 + 3;
                }else if(temp_one.type == 2 && temp_two.type == 2){ //aoi22
                    if(temp_one.predecessor_one == -1) c1 = 0;
                    else c1 = gate[temp_one.predecessor_one].cost;
                    if(temp_one.predecessor_two == -1) c2 = 0;
                    else c2 = gate[temp_one.predecessor_two].cost;
                    if(temp_two.predecessor_one == -1) c3 = 0;
                    else c3 = gate[temp_two.predecessor_one].cost;
                    if(temp_two.predecessor_two == -1) c4 = 0;
                    else c4 = gate[temp_two.predecessor_two].cost;
                    return c1 + c2 + c3 + +c4 + 4;
                }else{ // not match
                    return -1;
                }
           }
        }else return -1;
    }else if(vertices.type == 2){ //nand
        if(vertices.predecessor_one != -1 && vertices.predecessor_two != -1){
            temp_one = gate[vertices.predecessor_one];
            temp_two = gate[vertices.predecessor_two];
            for(int i =0 ; i<4 ; i++){
                min[i] = 1000;
            }
            if(temp_one.type == 1){  //nand3
                if(temp_one.predecessor_one != -1){
                    if(gate[temp_one.predecessor_one].type == 2){
                        if(gate[temp_one.predecessor_one].predecessor_one == -1) c1 = 0;
                        else c1 = gate[gate[temp_one.predecessor_one].predecessor_one].cost;
                        if(gate[temp_one.predecessor_one].predecessor_two == -1) c2 = 0;
                        else c2 = gate[gate[temp_one.predecessor_one].predecessor_two].cost;       
                        min[0] = c1 + c2 + gate[vertices.predecessor_two].cost + 3;
                    }else{
                        min[0] = 1000;
                    }
                }else{
                    min[0] = 1000;
                }
            }
            if(temp_one.type == 2){ //oai21
                if(temp_one.predecessor_one != -1 && temp_one.predecessor_two != -1){
                    if(gate[temp_one.predecessor_one].type == 1 && gate[temp_one.predecessor_two].type == 1){
                        if(gate[temp_one.predecessor_one].predecessor_one == -1) c1 = 0;
                        else c1 = gate[gate[temp_one.predecessor_one].predecessor_one].cost;
                        if(gate[temp_one.predecessor_two].predecessor_one == -1) c2 = 0;
                        else c2 = gate[gate[temp_one.predecessor_two].predecessor_one].cost;
                        min[1] = c1 + c2 + gate[vertices.predecessor_two].cost + 3;
                    }else{
                        min[1] = 1000;
                    }
                }else{
                    min[1] = 1000;
                }
            }
            if(temp_two.type == 1){  //nand3
                if(temp_two.predecessor_one != -1){
                    if(gate[temp_two.predecessor_one].type == 2){
                        if(gate[temp_two.predecessor_one].predecessor_one == -1) c1 = 0;
                        else c1 = gate[gate[temp_two.predecessor_one].predecessor_one].cost;
                        if(gate[temp_two.predecessor_one].predecessor_two == -1) c2 = 0;
                        else c2 = gate[gate[temp_two.predecessor_one].predecessor_two].cost;
                        min[2] = c1 + c2 + gate[vertices.predecessor_one].cost + 3;
                    }else{
                        min[2] = 1000;
                    }
                }else{
                    min[2] = 1000;
                }
            }
            if(temp_two.type == 2){ //oai21
                if(temp_two.predecessor_one != -1 && temp_two.predecessor_two != -1){
                    if(gate[temp_two.predecessor_one].type == 1 && gate[temp_two.predecessor_two].type == 1){
                        if(gate[temp_two.predecessor_one].predecessor_one == -1) c1 = 0;
                        else c1 = gate[gate[temp_two.predecessor_one].predecessor_one].cost;
                        if(gate[temp_two.predecessor_two].predecessor_one == -1) c2 = 0;
                        else c2 = gate[gate[temp_two.predecessor_two].predecessor_one].cost;
                        min[3] = c1 + c2 + gate[vertices.predecessor_one].cost + 3;
                    }else{
                        min[3] = 1000;
                    }
                }else{
                    min[3] = 1000;
                }
            }
            min_r = 1000;
            for(int i =0 ; i<4 ; i++){
                if(min[i]<min_r) min_r = min[i];
            }
            if(min_r == 1000) {
                return -1; //not match
            }else {
                return min_r;
            }
        }else if(vertices.predecessor_one != -1 && vertices.predecessor_two == -1){
            temp_one = gate[vertices.predecessor_one];
            if(temp_one.type == 1){  //nand3
                if(temp_one.predecessor_one != -1){
                    if(gate[temp_one.predecessor_one].type == 2){
                        if(gate[temp_one.predecessor_one].predecessor_one == -1) c1 = 0;
                        else c1 = gate[gate[temp_one.predecessor_one].predecessor_one].cost;
                        if(gate[temp_one.predecessor_one].predecessor_two == -1) c2 = 0;
                        else c2 = gate[gate[temp_one.predecessor_one].predecessor_two].cost;
                        return c1 + c2 + 3;
                    }else{
                        return -1;
                    }
                }else{
                    return -1;
                }
            }else if(temp_one.type == 2){ //oai21
                if(temp_one.predecessor_one != -1 && temp_one.predecessor_two != -1){
                    if(gate[temp_one.predecessor_one].type == 1 && gate[temp_one.predecessor_two].type == 1){
                        if(gate[temp_one.predecessor_one].predecessor_one == -1) c1 = 0;
                        else c1 = gate[gate[temp_one.predecessor_one].predecessor_one].cost;
                        if(gate[temp_one.predecessor_two].predecessor_one == -1) c2 = 0;
                        else c2 = gate[gate[temp_one.predecessor_two].predecessor_one].cost;
                        return c1 + c2 + 3;
                    }else{
                        return -1;
                    }
                }else{
                    return -1;
                }
            }else return -1;
        }else if(vertices.predecessor_one == -1 && vertices.predecessor_two != -1){
            temp_two = gate[vertices.predecessor_two];
            if(temp_two.type == 1){  //nand3
                if(temp_two.predecessor_one != -1){
                    if(gate[temp_two.predecessor_one].type == 2){
                        if(gate[temp_two.predecessor_one].predecessor_one == -1) c1 = 0;
                        else c1 = gate[gate[temp_two.predecessor_one].predecessor_one].cost;
                        if(gate[temp_two.predecessor_one].predecessor_two == -1) c2 = 0;
                        else c2 = gate[gate[temp_two.predecessor_one].predecessor_two].cost;
                        return c1 + c2 + 3;
                    }else{
                       return -1;
                    }
                }else{
                    return -1;
                }
            }else if(temp_two.type == 2){ //oai21
                if(temp_two.predecessor_one != -1 && temp_two.predecessor_two != -1){
                    if(gate[temp_two.predecessor_one].type == 1 && gate[temp_two.predecessor_two].type == 1){
                        if(gate[temp_two.predecessor_one].predecessor_one == -1) c1 = 0;
                        else c1 = gate[gate[temp_two.predecessor_one].predecessor_one].cost;
                        if(gate[temp_two.predecessor_two].predecessor_one == -1) c2 = 0;
                        else c2 = gate[gate[temp_two.predecessor_two].predecessor_one].cost;
                        return c1 + c2 + 3;
                    }else{
                        return -1;
                    }
                }else{
                   return -1;
                }
            }else return -1;
        }else return -1;
    }else return -1;
}

int main(int argc, char** argv){
    ifstream in_p;
    ifstream in_t;
    string pattern_tree;
    string testbench;
    string temp;
    string wire_string;
    int wire_label, wire_one, wire_two;
    int gate_number = 0;
    int cost[30];

    in_t.open(argv[2]);
    getline(in_t, temp); //module
    getline(in_t, temp); 
    getline(in_t, temp); // wire
    while(1){
        in_t >> temp ;
        if(temp.compare("NOT")==0){
            in_t >> temp ;
            wire_string = temp.substr(temp.find("(")+1,temp.find(",")-temp.find("(")-1);
            if(wire_string.compare("OUT")==0){
                gate[gate_number].have_gate = true;
                gate[gate_number].type = 1;
                gate[gate_number].cost = 1000;
                gate[gate_number].label = gate_number;
                in_t >> temp ;
                wire_string = temp.substr(0,temp.find(")"));
                if(wire_string.length() != 1){ //primary input
                    gate[gate_number].predecessor_one = -1;
                }else{
                    wire_one = int(wire_string[0]) - 97;
                    gate[gate_number].predecessor_one = wire_one;
                }
            }else{
                wire_label = int(wire_string[0]) - 97;
                if(!gate[wire_label].have_gate){
                    gate[wire_label].have_gate = true;
                    gate[gate_number].type = 1;
                    gate[gate_number].cost = 1000;
                    gate[gate_number].label = gate_number;
                    gate_number ++ ;
                    in_t >> temp ;
                    wire_string = temp.substr(0,temp.find(")"));
                    if(wire_string.length() != 1){ //primary input
                        gate[wire_label].predecessor_one = -1;
                    }else{
                        wire_one = int(wire_string[0]) - 97;
                        gate[wire_label].predecessor_one = wire_one;
                    }
                }
            }
        }else if(temp.compare("NAND")==0){
            in_t >> temp ;
            wire_string = temp.substr(temp.find("(")+1,temp.find(",")-temp.find("(")-1);
            if(wire_string.compare("OUT")==0){
                gate[gate_number].have_gate = true;
                gate[gate_number].type = 2;
                gate[gate_number].cost = 1000;
                gate[gate_number].label = gate_number;
                in_t >> temp ;
                wire_string = temp.substr(0,temp.find(","));
                if(wire_string.length() != 1){ //primary input
                    gate[gate_number].predecessor_one = -1;
                }else{
                    wire_one = int(wire_string[0]) - 97;
                    gate[gate_number].predecessor_one = wire_one;
                }
                in_t >> temp ;
                wire_string = temp.substr(0,temp.find(")"));
                if(wire_string.length() != 1){ //primary input
                    gate[gate_number].predecessor_two = -1;
                }else{
                    wire_two = int(wire_string[0]) - 97;
                    gate[gate_number].predecessor_two = wire_two;
                }
            }else{
                wire_label = int(wire_string[0]) - 97;
                if(!gate[wire_label].have_gate){
                    gate[wire_label].have_gate = true;
                    gate[gate_number].type = 2;
                    gate[gate_number].cost = 1000;
                    gate[gate_number].label = gate_number;
                    gate_number ++ ;
                    in_t >> temp ;
                    wire_string = temp.substr(0,temp.find(","));
                    if(wire_string.length() != 1){ //primary input
                        gate[wire_label].predecessor_one = -1;
                    }else{
                        wire_one = int(wire_string[0]) - 97;
                        gate[wire_label].predecessor_one = wire_one;
                    }
                    in_t >> temp ;
                    wire_string = temp.substr(0,temp.find(")"));
                    if(wire_string.length() != 1){ //primary input
                        gate[wire_label].predecessor_two = -1;
                    }else{
                        wire_two = int(wire_string[0]) - 97;
                        gate[wire_label].predecessor_two = wire_two;
                    }
                }
            }
        }else if (temp.compare("endmodule")==0){
            break;
        }
    } 
    cout << "minimum cost = " << mincost(gate[gate_number]) << endl;
    //printf("%d",gate[8].cost);
    in_t.close();
    return 0;
}