include <ESP8266WiFi.h>
 
const char* ssid = "Alunos";
const char* password = "harmoniabilingue";
 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  // prepare GPIO2
  pinMode(5, OUTPUT);
  digitalWrite(5, 0);
 
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);

  pinMode(14, OUTPUT);
  digitalWrite(14, 0);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
 
  }
 
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
 
  String buf = "";
 
  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  buf += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  buf += "<title>ESP8266 Web Server</title>";
  buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;}</style>";
  buf += "</head>";
  buf += "<h3>ESP8266 Web Server - System Logs</h3>";
  buf += "<p>GPIO14 <a href=\"?function=led14_on\"><button>ON</button></a> <a href=\"?function=led14_off\"><button>OFF</button></a></p>";
  buf += "<p>GPIO5 <a href=\"?function=led5_on\"><button>ON</button></a> <a href=\"?function=led5_off\"><button>OFF</button></a></p>";
  buf += "<p>GPIO4 <a href=\"?function=led4_on\"><button>ON</button></a> <a href=\"?function=led4_off\"><button>OFF</button></a></p>";
  buf += "<h4>Criado por Pedro Minatel</h4>";
  buf += "</html>\n";
 
  client.print(buf);
  client.flush();
 
  if (req.indexOf("led4_on") != -1)
    digitalWrite(4, 1);
  else if (req.indexOf("led4_off") != -1)
    digitalWrite(4, 0);
  else if (req.indexOf("led5_on") != -1)
    digitalWrite(5, 1);
  else if (req.indexOf("led5_off") != -1)
    digitalWrite(5, 0);
  else if (req.indexOf("led14_on") != -1)
    digitalWrite(14, 1);
  else if (req.indexOf("led14_off") != -1)
    digitalWrite(14, 0);
  else {
    Serial.println("invalid request");
    client.stop();
  }
  Serial.println("Client disonnected");
}
String css (){
  String Buf = "";

Buf +="<html>";
Buf +="<head>";
Buf +="<meta charset=\"utf-8\"><title>Semafaro</title></head>";
Buf +="<style>";
    //* mouse over link */
Buf +="a:link { color:#00FFB3;text-decoration: none;}a:visited {color: #00FFB3;}a:hover {";
Buf +="color: yellow;}.menu{padding: 0px;height: 50px; width: 50px;position: absolute;z-index: auto; top: 70px;}";
Buf +=".menuFonte {font-family: Gotham, \"Helvetica Neue\", Helvetica, Arial, sans-serif;font-size: 16px;color: #00FFB3;background:#000000; text-align:center;}";
Buf +=".logomarca { padding: 0px; height: 50px; width: 50px; position: absolute; z-index: auto; top: 0px; }.topo { padding: 0px; height: 50px; width: 310px; position: absolute;";
Buf +="z-index: auto; top: 0px; right: 0px; left: 100px;}.topoFonte { font-family: Gotham, \"Helvetica Neue\", Helvetica, Arial, sans-serif; font-size: 16px; color: red; text-align:right;}";
Buf +=".sinalVermelho{ padding: 0px; height: 50px; width: 50px; position: absolute; z-index: auto; top: 70px; left: 220px; background-color:red;}.sinalAmarelo{ padding: 0px; height:50px;";
Buf +="width: 50px; position: absolute; z-index: auto; top: 119px; left: 220px; background-color:yellow;}.sinalVerde{ padding: 0px; height: 50px; width: 50px; position: absolute; z-index: auto;";
Buf +="top: 165px; left: 220px; background-color:green;}.botVermelho{ border: none; height: 40px; width: 40px; position: absolute; z-index: auto; top: 73px; left: 300px; cursor: pointer; background-color:red;}";
Buf +=".botAmarelo{ border: none; height:40px; width: 40px; position: absolute; z-index: auto; top: 123px; left: 300px; cursor: pointer; background-color:yellow;}";
Buf +=".botVerde{ border: none; cursor: pointer; height: 40px; width: 40px; position: absolute; z-index: auto; top: 172px; left: 300px; background-color:green;}";
Buf +=".OFFline{ opacity:0.6; cursor: not-allowed;}</style>"
 return Buf;
}

String semafaro (){
  String Buf= "";
  Buf +="<body>";
Buf +="<div class=\"logomarca\">";
    Buf +="<img src=\"https://pbs.twimg.com/profile_images/378800000092669685/3f94b85b94f68c528624de7c8f9138a0_400x400.png\" alt=\"\" width=\"66\" height=\"66\" />";
Buf +="</div>";
 
Buf +="<div class=\"topo\">";    
    Buf +="<table width=\"300\" border=\"0\" cellpadding=\"2\">";
            Buf +="<tbody>";
              Buf +="<tr>";
                Buf +="<td class=\"topoFonte\" align=\"right\">Semafaro Wifi</td>";
              Buf +="</tr>";
              Buf +="<tr>";
                Buf +="<td class=\"topoFonte\" style=\"color: blue\" >Versão 1.0</td>";
              Buf +="</tr>";
            Buf +="</tbody>";
          Buf +="</table>";
    Buf +="</div>";
  
Buf +="<div class=\"menu\">";    
Buf +="<table border=\"0\" width=\"100\" cellpadding=\"1\">";
  Buf +="<tbody>";  
     Buf +="<tr>";
        Buf +="<td class=\"menuFonte\"  width=\"100\" height=\"25\"><a href=\"relogio.html\" target=\"_parent\">relogio</a></td>";
      Buf +="</tr>";
      Buf +="<tr bgcolor=\"#FFFFFF\" style=\"color: #000000\">";
        Buf +="<td  class=\"menuFonte\" width=\"100\" height=\"25\"><a href=\"semafaro.html\" target=\"_parent\">semafaro</a></td>";
      Buf +="</tr>";
      Buf +="<tr bgcolor=\"#FFFFFF\">";
        Buf +="<td  class=\"menuFonte\" width=\"100\" height=\"25\"><a href=\"login.html\" target=\"_parent\">login/senha</a></td>";
      Buf +="</tr>";
      Buf +="<tr bgcolor=\"#FFFFFF\">";
        Buf +="<td class=\"menuFonte\" width=\"100\" height=\"25\"><a href=\"deslogar.html\" target=\"_parent\">deslogar</a></td>";
      Buf +="</tr>";
    Buf +="<tr bgcolor=\"#FFFFFF\">";
        Buf +="<td class=\"menuFonte\" width=\"100\" height=\"25\"><a href=\"deslogar.html\" target=\"_parent\">ajuda</a></td>";
      Buf +="</tr>"
    Buf +="</tbody>";
  Buf +="</table>";  
  Buf +="</div>";
Buf +="<div class=\"sinalVermelho\"></div>";
Buf +="<div class=\"sinalAmarelo\"></div>";
Buf +="<div class=\"sinalVerde\"></div>";
Buf +="<div class=\"botVermelho\"><a href=\"semafaro_vermelho.html\" target=\"_parent\">vermelho</a></div>";
Buf +="<div class=\"botAmarelo\"><a href=\"semafaro_amarelo.html\" target=\"_parent\">amarelo</a></div>";
Buf +="<div class=\"botVerde\"><a href=\"semafaro_verde.html\" target=\"_parent\">verde</a></div>";

Buf +="</body>";

Buf +="</html>";
 return Buf;
}


