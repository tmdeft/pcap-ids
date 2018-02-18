@extends('master')
@section('title', 'Хянах самбар')
@section('navigation')
  <li class="active"><a href="/dashboard">Хянах самбар</a></li>
  <li><a href="/app">Хэмжээсийн график</a></li>
  <li><a href="/doslog">Халдлагын бүртгэл</a></li>
@endsection
@section('scripts')
  <script src="/js/jquery.min.js"></script>
  <script src="/js/bootstrap.min.js"></script>
  <script src="/js/jquery.flot.js"></script>
  <script src="/js/networkflow.js"></script>
@endsection
@section('content')
<!-- The Modal -->
    <div class="modal fade" id="blue-modal" tabindex="-1" role="dialog" aria-labelledby="blue-modal-label" data-color="blue">
      <div class="modal-dialog" role="document">
        <div class="modal-content">
          <div class="modal-header">
            <button type="button" class="close btn-close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
            <h4 class="modal-title" id="blue-modal-title">Халдлагад өртлөө</h4>
          </div>
          <div class="modal-body">
            Халдагчийн IP хаяг : <span id="attackerIp"></span>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-default btn-close" data-dismiss="modal">Хаах</button>
          </div>
        </div>
      </div>
    </div>
    <div id="modal-backdrop" class="modal-backdrop-transparent modal-transition"></div>
<!-- Body -->
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
