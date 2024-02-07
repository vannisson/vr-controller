scene = document.getElementById("scene");
redLed = document.getElementById("led01-button");
greenLed = document.getElementById("led02-button");
currentLed = document.getElementById("current-led");

currentElement = undefined;

const url = "mqtt://127.0.0.1:9001"

const client = mqtt.connect(url);

client.on('connect', function () {})


AFRAME.registerComponent("clicable", {
  init: function () {
    let el = this.el;

    this.onRaycastHit = (evt) => {
      currentElement = el;
    };

    this.onRaycastClear = (evt) => {
      currentElement = undefined;
    };

    this.el.addEventListener("raycaster-intersected", this.onRaycastHit);
    this.el.addEventListener(
      "raycaster-intersected-cleared",
      this.onRaycastClear
    );
  },

  remove: function () {
    this.el.removeEventListener("raycaster-intersected", this.onRaycastHit);
    this.el.removeEventListener(
      "raycaster-intersected-cleared",
      this.onRaycastClear
    );
  },
});

AFRAME.registerComponent('led-commands',{
  init: function () {
    this.el.addEventListener('triggerdown', this.mqttLedPublisher);
  },
  mqttLedPublisher: function (evt) {
      if (currentElement != undefined){
          switch (currentElement.id) {
              case "led01-button":
                  client.publish('mqtt/esp32', 'Red')
                  redLed.setAttribute("material", "color: red; transparent: true; opacity: 0.3")
                  greenLed.setAttribute("material", "color: green; transparent: false; opacity: 1")
                  currentLed.setAttribute("material", "color: red")
                  break;
  
              case "led02-button":
                  client.publish('mqtt/esp32', 'Green')
                  redLed.setAttribute("material", "color: red; transparent: false; opacity: 1")
                  greenLed.setAttribute("material", "color: green; transparent: true; opacity: 0.3")
                  currentLed.setAttribute("material", "color: green")
                  break;
          }
      }
  }
});