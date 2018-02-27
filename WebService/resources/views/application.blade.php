@extends('master')
@section('title', 'Хэмжээсийн график')
@section('navigation')
  <li><a href="/dashboard">Хянах самбар</a></li>
  <li class="active"><a href="/app">Хэмжээсийн график</a></li>
  <li><a href="/doslog">Халдлагын бүртгэл</a></li>
  <script src="/js/jquery.min.js"></script>
  <script src="/js/bootstrap.min.js"></script>
  <script src="/js/raphael.min.js"></script>
  <script src="/js/morris.min.js"></script>
  <script src="/js/bardata.js"></script>
@endsection
@section('content')
  <div class="row">
    <div class="col-lg-6">
      <div class="panel panel-default">
        <div class="panel-heading">
          Хэмжээгээр
        </div>
<!-- /.panel-heading -->
        <div class="panel-body">
          <div id="size-bar-chart"></div>
        </div>
<!-- /.panel-body -->
      </div>
<!-- /.panel -->
    </div>
    <div class="col-lg-6">
      <div class="panel panel-default">
        <div class="panel-heading">
          Портоор
        </div>
<!-- /.panel-heading -->
        <div class="panel-body">
          <div id="port-bar-chart"></div>
        </div>
<!-- /.panel-body -->
      </div>
<!-- /.panel -->
    </div>
  </div>
@endsection
