#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <vector>
#include <utility>

struct fecha{
    int dia = 0;
    int mes = 0;
    int año = 0;
};

struct DateFormatException : public std::exception
{
	const char * what () const throw () override
    {
    	return "Bad date formatting.";
    }
};

struct DateException : public std::exception
{
	const char * what () const throw () override
    {
    	return "Query date before birth date.";
    }
};

// bool CorrectDateFormat(fecha _fecha){
//     bool valid_day = false;
//     bool valid_month = false;
//     bool valid_year = false;
    
//     if ((_fecha.mes >= 1) || (_fecha.mes <= 12))
//     {
//         valid_month = true;
//     }

//     if ((_fecha.mes == 2) && (_fecha.año % 4 == 0) && (_fecha.dia<=29 && _fecha.dia>=1))
//     {
//         valid_day = true; 
//     }
//     else if ((_fecha.mes == 2) && (_fecha.año % 4 != 0) && (_fecha.dia<=28 && _fecha.dia>=1) )
//     {
//         valid_day = true; 
//     }

//     if ((_fecha.mes == 1 || _fecha.mes == 3 || _fecha.mes == 5 || _fecha.mes == 7 ||
//         _fecha.mes == 8 || _fecha.mes == 10 || _fecha.mes == 12) && ( _fecha.dia<=31 && _fecha.dia>=1) )
//     {
//         valid_day = true; 
//     }
//     else if ((_fecha.mes == 4 || _fecha.mes == 6 || _fecha.mes == 9 || _fecha.mes == 11) && (_fecha.dia<=30 && _fecha.dia>=1) )
//     {
//         valid_day = true; 
//     }
    

//     if ((_fecha.año >= 999) || (_fecha.año <= 10000))
//     {
//         valid_year = true;
//     }

//     return (valid_day && valid_month && valid_year);
// }

bool esBisiesto(int year) {
  return (((year % 4 == 0) &&
          (year % 100 != 0)) ||
          (year % 400 == 0));
}
 
bool CorrectDateFormat(fecha _fecha){
    int y = _fecha.año;
    int m = _fecha.mes;
    int d = _fecha.dia;

    // valores maximos y minimos
    // de meses y días
    if (m < 1 || m > 12)
      return false;
    if (d < 1 || d > 31)
      return false;
 
    // Caso febrero, años bisiestos
    if (m == 2)
    {
        if (esBisiesto(y))
          return (d <= 29);
        else
          return (d <= 28);
    }
 
    // Considerar máximo de dias de cada mes
    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
        return (d <= 30);
 
    return true;
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
    if (pos == std::string::npos)
        throw DateFormatException();

    std::string dia_s = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());

    pos = input.find(delimiter);
    if (pos == std::string::npos)
        throw DateFormatException();

    std::string mes_s = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());
    
    pos = input.find(delimiter);
        
    std::string año_s = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());

    if (dia_s.empty() || mes_s.empty() || año_s.empty())
        throw DateFormatException();

    int dia = 0;
    int mes = 0;
    int año = 0;
    
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
        throw DateFormatException();
    }
    
    return date;  

}

int main(int argc, char *argv[]){
    std::string TESTING = "-t";
    if (argc > 1){
        if (!TESTING.compare(argv[1])){
            // run coverage tests
            std::cout << "Running Tests:\n";

            std::vector<std::pair<std::string,std::string>> tests = {
                {"21/09/1997", "31/05/2022"},   // Valid Age
                {"29/02/2020", "28/02/2021"},   // Invalid Age 
                {"29/02/2020", "28/02/2021"},   // Invalid Age
                {"01/03/2000", "01/03/2018"},   // Valid Age, Same Date
                {"01/02/2000", "01/03/2018"},   // Valid Age, Larger Month
                {"01/04/2000", "01/03/2018"},   // Invalid Age, Smaller Month
                {"01/03/2000", "02/03/2018"},   // Valid Age, Larger Day
                {"02/03/2000", "01/03/2018"},   // Invalid Age, Smaller Day
                {"31/12/1999", "31/12/1998"},   // Date Exception, Year
                {"31/12/1999", "01/01/1999"},   // Date Exception, Month
                {"31/12/9999", "30/12/9999"},   // Date Exception, Day
                {"33/01/1980", "24/01/1998"},   // Date Format Exception, Day
                {"01/24/1980", "24/01/1998"},   // Date Format Exception, Month
                {"12/01/1980", "24/01/0001"},   // Date Format Exception, Year
                {"/", "/"},                     // Date Format Exception, Wrong Characters 1
                {"//", "//"},                   // Date Format Exception, Wrong Characters 2
                {"", ""},                       // Date Format Exception, Wrong Characters 3
                {"a/b/c", "c/d/e"},             // Date Format Exception, Wrong Characters 4
            };

            std::vector<int> test_results = {1, 0, 0, 1, 1,0,1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
            
            int i = 0;
            int passed_cnt = 0;
            for (auto test : tests){
                int result = 0;
                try{
                    std::cout << " * nac: " << std::get<0>(test) << ", ";
                    std::cout << "con: " << std::get<1>(test)  << '\n';
                    result = CheckAdultAge(DateParser(std::get<0>(test)), DateParser(std::get<1>(test)));
                    std::cout << "-> Result: " << result << " | ";
                    
                }
                catch(const std::exception& e){
                    std::cerr << "-> Exception: " << e.what() << " | ";
                    result = -1;
                }
                if (test_results[i] == result){
                  ++passed_cnt;
                  std::cout << "PASS" << '\n';
                }
                else
                  std::cout << "FAIL" << '\n';
                ++i;
            }
            std::cout << "\n------------------\n-> ";
            std::cout << passed_cnt << " / " << test_results.size() << " tests passed\n";
            std::cout << "Tests Finished\n";
            return 0;
        }
        std::cerr << "Wrong argument";
        return 1;
    }
    else{
        // run program as normal
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
        catch(const std::exception& e){
            std::cerr << "Exception: " << e.what() << "\n";
            return 1;
        }
    }

}