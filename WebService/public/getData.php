<?php
  $host = "localhost";
  $port = 5555;
  $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
  $result = socket_connect($socket,"localhost","5555");
  socket_write($socket,"test",strlen("test"));
  $result = socket_read($socket,65536);
  socket_close($socket);
  $dataarr = explode(",",$result);
  // $cData->TCP = $dataarr[0];
  // $cData->UDP = $dataarr[1];
  // $cData->ICMP = $dataarr[2];
  // $cData->IGMP = $dataarr[3];
  // $cData->Others = $dataarr[4];
  // $cData->Total = $dataarr[5];
  echo json_encode($dataarr);
?>
