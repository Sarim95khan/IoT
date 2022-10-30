import { connect } from "mqtt";

const client = connect("mqtt://broker.mqttdashboard.com");

client.publish('sarim/message', 'MY message at HiveMQ broker');

