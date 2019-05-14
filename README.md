# so2_projects

Programy stworzone na projekt z Systemów Operacyjnych 2 - programy wielowątkowe w C++.
Użyte biblioteki:
 - ncurses
 - pthreads

Poszczególne projekty:
  - 01_balls - co 5 sekund program wysyła piłeczkę w 1 z 8 kierunków. Kierunek losowy, 3 typy prędkości, piłeczki nie odbijają się. Podstawy wielowątkowości; tworzenie, kończenie.
       ```sh 
        g++ src/Ball.cpp main.cpp -lncurses && ./main.out
  - 02_balls - rozwinięcie pierwszego projektu. Wydzielenie obszaru, w którym może być tylko "n" kulek. Jeśli jakaś kulka chce wleciec ponad stan to jest usypiana i czeka aż zrobi się miejsce. Zasada kolejkowania: first in first out.
       ```sh
        g++ src/Ball.cpp src/Window.cpp main.cpp -lncurses && ./main.out
  - 03_shop_simulation - symulacja sklepu.  

     Są trzy typy produktów:
     - jajka - generowane w czasie Tj
     - bułki - generowane w czasie Tb
     - wędliny - generowane w czasie Tw
     Jest jedna lada, z której klienci biorą produkty
     
     Są trzy kasy. Klient jest obsługiwany w czasie, który jest obliczany na podstawie produktów i numeru kasy
     
     Generują się klienci, których droga wygląda następująco:
     - wejście do sklepu
     - lada z produktami
     - kolejka do kas
     - wyjście ze sklepu
