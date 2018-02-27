<?php
  $host = "192.168.1.8";
  $port = 5555;
  $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
  $result = socket_connect($socket,"localhost","5555");
  socket_write($socket,"1",strlen("1"));
  $result = socket_read($socket,65536);
  socket_close($socket);
  $dataarr = explode(",",$result);
  $httpData = array('y' => '80', 'a' => $dataarr[0]);
  $httpsData = array('y' => '443', 'a' => $dataarr[1]);
  $dnsData = array('y' => '53', 'a' => $dataarr[2]);
  echo json_encode(array($httpData,$httpsData,$dnsData));
?>
