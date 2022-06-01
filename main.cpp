#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <vector>

struct fecha{
    int dia = 0;
    int mes = 0;
    int año = 0;
};

struct DateFormatException : public std::exception
{
	const char * what () const throw ()
    {
    	return "Bad date formatting.";
    }
};

struct DateException : public std::exception
{
	const char * what () const throw ()
    {
    	return "Query date before birth date.";
    }
};


bool CorrectDateFormat(fecha _fecha){
    bool valid_date = false;
    
    if ((_fecha.mes >= 1) || (_fecha.mes <= 12))
    {
        valid_date = true;
    }
    if ((_fecha.mes == 1 || _fecha.mes == 3 || _fecha.mes == 5 || _fecha.mes == 7 ||
        _fecha.mes == 8 || _fecha.mes == 10 || _fecha.mes == 12) && ( _fecha.dia<=31 || _fecha.dia>=1) )
    {
        valid_date = true; 
    }
    else if ((_fecha.mes == 4 || _fecha.mes == 6 || _fecha.mes == 9 || _fecha.mes == 11) && (_fecha.dia<=30 || _fecha.dia>=1) )
    {
        valid_date = true; 
    }
    else if ((_fecha.mes == 2) && (_fecha.año % 4 == 0) && (_fecha.dia<=29 || _fecha.dia>=1))
    {
        valid_date = true; 
    }
    else if ((_fecha.mes == 2) && (_fecha.año % 4 != 0) && (_fecha.dia<=28 || _fecha.dia>=1) )
    {
        valid_date = true; 
    }
    else if ((_fecha.año >= 999) || (_fecha.año <= 10000))
    {
        valid_date = true;
    }

    return valid_date;
}

bool QueryDateValidation(fecha nacimiento, fecha consulta ){
    if (consulta.año < nacimiento.año){
        return false;
    }else if (consulta.mes < nacimiento.mes && consulta.año == nacimiento.año){
        return false;
    }else if (consulta.dia < nacimiento.dia && consulta.año == nacimiento.año && consulta.mes == nacimiento.mes){
        return false;
    }
    return true;
}

bool CheckAdultAge(fecha nacimiento, fecha consulta) {
    if (!QueryDateValidation(nacimiento, consulta))
        throw DateException();

    int edadAnios = consulta.año - nacimiento.año;
    if(edadAnios == 18) { 
        if(consulta.mes == nacimiento.mes) {
            if(consulta.dia >= nacimiento.dia) {
                return true;
            }
            else {
                return false;
            }
        }
        else if(consulta.mes > nacimiento.mes) {
            return true;
        }
        else {
            return false;
        }
    }
    else if(edadAnios > 18) {
        return true;
    }
    else {
        return false;
    }
}

fecha DateParser(std::string input){
    size_t pos = 0;
    std::string delimiter = "/";
    
    pos = input.find(delimiter);
    std::string dia_s = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());

    pos = input.find(delimiter);
    std::string mes_s = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());
    
    pos = input.find(delimiter);
    std::string año_s = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());

    int dia, mes, año = 0;
    
    try{
        dia = stoi(dia_s);
        mes = stoi(mes_s);
        año = stoi(año_s);
    }
    catch(...) {
        throw DateFormatException();
    }   

    fecha date = {dia,mes,año};
    
    if (!CorrectDateFormat(date)){
        date.dia = 0; date.mes = 0; date.año = 0;
        std::cout<<"xd";
        throw DateFormatException();
    }
    
    return date;  

}

int main() {
    std::string nac_input;
    std::cout << "Ingresar fecha de Nacimiento con el formato DD/MM/AAAA: " << std::endl;
    std::cin >> nac_input;

    std::string con_input;
    std::cout << "Ingresar fecha de Consulta con el formato DD/MM/AAAA: " << std::endl;
    std::cin >> con_input;

    try{
        fecha nac = DateParser(nac_input);
        fecha con = DateParser(con_input);

        if (CheckAdultAge(nac,con))
            std::cout << "Edad Válida, mayor a 18 años.\n";
        else 
            std::cout << "Edad no Válida, menor a 18 años.\n";
        return 0;
    }
    catch(std::exception& e){
        std::cerr << "Exception: " << e.what();
        return 1;
    }

    // // testing

    // std::vector<std::string> nac {"21/09/1997", "29/02/2020", "29/02/2020", "31/12/9999", "01/24/1980"};
    // std::vector<std::string> con {"31/05/2022", "28/02/2021", "01/03/2021", "01/01/9999", "24/01/1998"};

    // for (int i = 0; i < nac.size(); ++i){
    //     std::cout << "nac: " << nac[i] << '\n';
    //     std::cout << "con: " << con[i] << '\n';
    //     auto result = CheckAdultAge(DateParser(nac[i]), DateParser(con[i]));
    //     std::cout << "result: " << result;
    // }


}