# Async Webserver on ESP32
##### Libraries used:
1. [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) for generating http and wesockets request asynchronously.
2. [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) is a dependency for ESPAsyncWebServer library so we won't be interacting with it directly.
##### Installation:
- Download the zip file or clone the repo and copy it into your arduino libraries folder 
##### Folder structure:
- [data](https://github.com/AdityaGawali/esp32AsyncWebServer/tree/master/data)
   - webpage.html -> Webpage with JavaScript for server to host
- [rs232_working_test](https://github.com/AdityaGawali/esp32AsyncWebServer/tree/master/rs232_working_test)
    - rs232_working_test.ino -> RS232 test code to be merged with main code
- [README.md](https://github.com/AdityaGawali/esp32AsyncWebServer/blob/master/README.md) -> This file
- [espAsynchtmlJS.ino](https://github.com/AdityaGawali/esp32AsyncWebServer/blob/master/espAsynchtmlJS.ino) -> Main code consisting of Server serving http requests and websocket connection
##### Usage:
1. Build and flash espAsynchtmlJS.ino into ESP32 and open Serial Terminal,ESP32 will create a local server and print it's IP on local network
2. Copy the IP so obtained and assign  it to variable "ip" in webpage.html 
        var ip = "192.168.0.101"
3. Open Browser and point it to this ip address and you have now established connection with the server.

##### Tasks:
1. Merging RS232 code into server code
2. getting data from RS232 and sending messages to client(Control logic)
3. Eliminating the need of manually setting the ip variable in webpage.html