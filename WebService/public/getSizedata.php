<?php
  $host = "192.168.1.8";
  $port = 5555;
  $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
  $result = socket_connect($socket,"localhost","5555");
  socket_write($socket,"2",strlen("2"));
  $result = socket_read($socket,65536);
  socket_close($socket);
  $dataarr = explode(",",$result);
  $first = array('y' => '(1500+)', 'a' => $dataarr[0]);
  $second = array('y' => '(1499-750)', 'a' => $dataarr[1]);
  $third = array('y' => '(749-512)', 'a' => $dataarr[2]);
  $fourth = array('y' => '(511-97)', 'a' => $dataarr[3]);
  $fifth = array('y' => '(96-)', 'a' => $dataarr[4]);
  echo json_encode(array($first, $second, $third, $fourth, $fifth));
?>
