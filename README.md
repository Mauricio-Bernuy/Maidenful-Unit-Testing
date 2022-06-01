# Maidenful Unit Testing
 
# Compile and Run (Tests)
```cmd
g++ -O0 main.cpp -o program --coverage && program -t
```

# SonarCloud with Coverage
```cmd
build-wrapper-win-x86-64.exe --out-dir bw-output g++ -O0 main.cpp -o program --coverage

program -t

gcov main.cpp

move *.gcov ./gcov (cmd), mv *.gcov ./gcov (bash) 

sonar-scanner.bat  -D"sonar.organization=mauricio-bernuy"  -D"sonar.projectKey=Mauricio-Bernuy_Maidenful-Unit-Testing"  -D"sonar.sources=."  -D"sonar.cfamily.build-wrapper-output=bw-output"  -D"sonar.host.url=https://sonarcloud.io"  -D"sonar.cfamily.gcov.reportsPath=./gcov"
```