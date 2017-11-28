<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="PCAP-IDS">
    <meta name="author" content="J.IN12D067 MUST-SICT">
  	<title>PCAP-IDS @yield('title')</title>
    <link href="/vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="/vendor/metisMenu/metisMenu.min.css" rel="stylesheet">
    <link href="/dist/css/sb-admin-2.css" rel="stylesheet">
    <link href="/vendor/morrisjs/morris.css" rel="stylesheet">
    <link href="/vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">
    <link hrf="/css/custom.css" rel="stylesheet" type="text/css">
    <link href="https://fonts.googleapis.com/css?family=Roboto+Condensed" rel="stylesheet">
    @yield('scripts')
  </head>
  <body>
    @section('navbar')
      <nav class="navbar navbar-inverse">
        <div class="container-fluid">
          <div class="navbar-header">
            <a class="navbar-brand" href="/dashboard">PCAP-IDS</a>
          </div>
          <ul class="nav navbar-nav">
            @yield('navigation')
          </ul>
        </div>
      </nav>
    @show
    <div class='container'>
      @yield('content')
    </div>
  </body>
</html>
