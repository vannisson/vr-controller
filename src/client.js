//const mqtt = require("mqtt");


// // Create an MQTT client instance
// const options = {
//   // Clean session
//   clean: true,
//   connectTimeout: 4000,
//   // Authentication
//   clientId: 'emqx_test',
//   username: 'emqx_test',
//   password: 'emqx_test',
// }


// Receive messages
// client.on('message', function (topic, message) {
//   // message is Buffer
//   console.log(`Received message on topic ${topic}: ${message.toString()}`);
//   if (message.toString() == "Red"){
//     client.publish('mqtt/esp32', 'JS: Ok, its Red')
//   } else if (message.toString() == "Green"){
//     client.publish('mqtt/esp32', 'JS: Ah, its Green now')
//   }
//   // Agora, você pode adicionar o código para lidar com a mensagem recebida como desejar
// });

// Mantenha o script em execução
// process.on('SIGINT', function () {
//   client.end();
//   process.exit();
// });