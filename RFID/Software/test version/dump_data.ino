void dump_data() {
  while(client.available())
  {
    client.read();
    delay(1);
  }
}
