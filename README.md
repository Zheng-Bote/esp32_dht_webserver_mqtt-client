<div id="top"></div>
<br />
<div align="center">
<h3 align="center">ESP32 DHT temperature/humidity Wifi Webserver & MQTT client</h3>

  <p align="center">
      Arduino prog for DHT11, DHT22 (AM2302), DHT21 (AM2301) sensor
      <br/>
      with WiFi, dis-/enabled Webserver and dis-/enabled MQTT client
      <br/>
      <br/>
    <a href="https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client/wiki"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client/issues">Report Bug</a>
    ·
    <a href="https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client/issues">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project
### ESP32 temperature/humidity Wifi Webserver & MQTT client
Arduino prog for DHT11, DHT22 (AM2302), DHT21 (AM2301)sensor with WiFi, dis-/enabled Webserver and dis-/enabled MQTT client
* optional: show Temperature and Humidity on Website (refresh every 15 seconds)
* optional: MQTT client intervall publishing (customizable)
* optional: MQTT publish data and do ESP32 deep sleep intervall (customizable) 

**Screenshots**

Webserver / website with firmware update message

<img src="https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client/wiki/img/web_02.png" />

MQTT client (Terminal)

<img src="https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client/wiki/img/terminal.png" />

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

install the Arduino IDE or use the web online version

### Prerequisites

* PC or Laptop with Windows, MacOS or Linux *_^
* ESP32 connected with sensor
* DHT11 or DHT22 (AM2302) or DHT21 (AM2301) sensor
* install the Arduino IDE
  `https://www.arduino.cc/en/software`
* or use Arduino IDE online
  `https://create.arduino.cc/editor`
* some included libraries needs additional Arduino libraries (e.g. PubSubClient. See header comments)
* MQTT PubSubClient

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client.git
   ```
2. fill in your credentials
   `credentials.h`
   * WiFi settings (SSID, password)
   * start MQTT yes|no, MQTT publish intervall ...
   * start Webserver yes|no
   * publish MQTT and do ESP32 deep sleep ...
4. load firmware on ESP32

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

- [ ] optional automatic firmware update
- [ ] optional WifiManager
- [ ] enabling MQTT subscribing
- [ ] ???

Maybe a Kanban board will be established (soon)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

ZHENG Robert Zhèng Bó Tè 郑 伯特

Project Link: [https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client](https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client)

<p align="right">(<a href="#top">back to top</a>)</p>

