@extends('master')
@section('title', 'dashboard')
@section('navigation')
  <li class="active"><a href="/dashboard">Dashboard</a></li>
  <li><a href="/app">Application Layers</a></li>
  <li><a href="/doslog">DoS Log</a></li>
@endsection
@section('scripts')
  <script src="/js/jquery.min.js"></script>
  <script src="/js/bootstrap.min.js"></script>
  <script src="/js/jquery.flot.js"></script>
  <script src="/js/networkflow.js"></script>
@endsection
@section('content')
<div class="row">
              <div class="col-lg-3 col-md-6">
                  <div class="panel panel-primary">
                      <div class="panel-heading">
                          <div class="row">
                              <div class="col-xs-3">
                                  <i class="fa fa-comments fa-5x"></i>
                              </div>
                              <div class="col-xs-9 text-right">
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
                                  <i class="fa fa-tasks fa-5x"></i>
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
                                  <i class="fa fa-shopping-cart fa-5x"></i>
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
                                  <i class="fa fa-support fa-5x"></i>
                              </div>
                              <div class="col-xs-9 text-right">
                                  <div class="huge">0</div>
                                  <div>Total attacks</div>
                              </div>
                          </div>
                      </div>
                  </div>
              </div>
              <div class="col-lg-12">
                    <div class="panel panel-default">
                        <div class="panel-heading">
                            NIC : <span id="ifnameId"></span><br>
                            IP Address : <span id="ipaddressId"></span>
                        </div>
                        <!-- /.panel-heading -->
                        <div class="panel-body">
                            <div class="flot-chart">
                                <div class="flot-chart-content" id="networkFlow"></div>
                            </div>
                        </div>
                        <!-- /.panel-body -->
                    </div>
                    <!-- /.panel -->
              </div>
          </div>
@endsection
