Aplikacja simple logger. Składa się z biblioteki logserver pozwalającej
uruchomić serwer nasłuchujący przychodzących wiadomości do logowania przy użyciu
socket'ów za równo w sieci podając adres IP lub nazwę domenową, jak i lokalnie
(przez adres 127.0.0.1.

Drugą częścią aplikacji jest biblioteka logger, która pozwala w łatwy sposób
stworzyć klienta wysyłającego wiadomości do serwera logującego. Ona także
pozwala łączyć się z serwerem przy użyciu socketów. 

Oprócz tego stworzono biblioteki pomocnicze. Pierwszą jest logsmg, która pozwala
ustandaryzować format przesyłanych wiadomości. Biblioteka przesyła dane w formie
tekstowej, a nie binarnej, dzięki czemu jest łatwiejsza do monitorowania,
modyfikowania, a także wykorzystania w innych projektach. Jest także biblioteka
buffer, która zapewnia szablon bufora do przechowywania wiadomości u klienta
przed ich wysłaniem. Klasa bufora jest szablonem, także można go wykorzystywać
także do innych typów danych. Ostatnią bibliteką pomocniczą jest functions,
która wykorzystuje bibliotekę boost by stworzyć popularną funkcję explode,
wykorzystywaną do podzielenia w serwerze danych przesłanych przez klienta.

W katalogu src znajdują się wszystkie kody źródłowe stworzone na potrzeby
projektu. Katalog doc zawiera dokumentację wygenerowaną przez doxygen. 

Katalog test zawiera 4 podkatalogi:
buf_test - który pozwala przetestować działanie bufora wiadomości,
log_test - który pozwala przetestować działanie samych wiadomości,
logger_test - test aplikacji klienckiej,
server_test - test aplikacji serwerowej,

Aby w pełni przetestować serwer i klienta, należy uruchomić serwer z katalogu
serwer_test aplikację serwerową i z katalogu logger_test aplikację kliencką.
