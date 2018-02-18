@extends('master')
@section('title', 'Attack Log')
@section('navigation')
  <li><a href="/dashboard">Dashboard</a></li>
  <li><a href="/app">Application Layers</a></li>
  <li class="active"><a href="/doslog">DoS Log</a></li>
@endsection
@section('scripts')
  <script src="/js/jquery.min.js"></script>
  <script src="/js/tableScript.js"></script>
@endsection
@section('content')
  <div class="container">
    <h1>DoS Log</h1>
  	<div class="row">
          <div class="col-md-3">
              <form action="#" method="get">
                  <div class="input-group">
                      <!-- USE TWITTER TYPEAHEAD JSON WITH API TO SEARCH -->
                      <input class="form-control" id="system-search" name="q" placeholder="Search for" required>
                      <span class="input-group-btn">
                          <button type="submit" class="btn btn-default"><i class="glyphicon glyphicon-search"></i></button>
                      </span>
                  </div>
              </form>
          </div>
  		<div class="col-md-9">
      	 <table class="table table-list-search">
                      <thead>
                          <tr>
                              <th>No.</th>
                              <th>Time</th>
                              <th>IP Address</th>
                              <th>MAC Address</th>
                              <th>Port</th>
                          </tr>
                      </thead>
                      <tbody>
                          @foreach($data as $key => $elem)
                              <tr>
                                  <th>{{$elem->ID}}</th>
                                  <th>{{$elem->Time}}</th>
                                  <th>{{$elem->IP_Address}}</th>
                                  <th>{{$elem->MAC_Address}}</th>
                                  <th>{{$elem->Port}}</th>
                              </tr>
                          @endforeach
                      </tbody>
                  </table>
  		</div>
  	</div>
  </div>
@endsection
