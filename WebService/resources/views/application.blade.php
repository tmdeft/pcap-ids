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
    <div class="col-lg-3 col-md-6">
      <div class="panel panel-primary">
        <div class="panel-heading">
          <div class="row">
            <div class="col-xs-3">
              <i class="glyphicon glyphicon-menu-down fa-5x"></i>
            </div>
            <div class="col-xs-9 text-center">
              <div class="huge" id="httpsCount">0</div>
              <div>HTTPS</div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="col-lg-3 col-md-6">
      <div class="panel panel-green">
        <div class="panel-heading">
          <div class="row">
            <div class="col-xs-3">
              <i class="glyphicon glyphicon-menu-down fa-5x"></i>
            </div>
            <div class="col-xs-9 text-right">
              <div class="huge" id="httpCount">0</div>
              <div>HTTP</div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="col-lg-3 col-md-6">
      <div class="panel panel-yellow">
        <div class="panel-heading">
          <div class="row">
            <div class="col-xs-3">
              <i class="glyphicon glyphicon-menu-down fa-5x"></i>
            </div>
            <div class="col-xs-9 text-right">
              <div class="huge" id="dnsCount">0</div>
              <div>DNS</div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="col-lg-3 col-md-6">
      <div class="panel panel-red">
        <div class="panel-heading">
          <div class="row">
            <div class="col-xs-3">
              <i class="fa fa-exclamation-circle fa-5x"></i>
            </div>
            <div class="col-xs-9 text-right">
              <div class="huge" id="attackCountId">0</div>
              <div>Нийт халдлага</div>
            </div>
          </div>
        </div>
        <a href="/doslog">
          <div class="panel-footer">
            <span class="pull-left">Дэлгэрэнгүй</span>
            <span class="pull-right"><i class="fa fa-arrow-circle-right"></i></span>
            <div class="clearfix"></div>
          </div>
        </a>
      </div>
    </div>
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
