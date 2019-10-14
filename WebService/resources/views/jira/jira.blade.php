<!-- Call backend layout -->
@extends('layout.__back')

<!-- Set called layout title -->
@section('title', 'Jira Statistics')

@section('pagecss')
  	<link href="{{ asset('static/vendor/datatables/dataTables.bootstrap4.min.css') }}" rel="stylesheet">
	<link href="{{ asset('static/css/bootstrap-datepicker.min.css') }}" rel="stylesheet">
@endsection

<!-- Set called layout body -->
@section('body')
    <div class="row">
		<div class="col-xl-12 col-lg-12">
			<div class="card shadow mb-4">
				<div class="card-header py-3">
					<div class="row">
						<div class="col-lg-4">
							<h4 class="small font-weight-bold">Хайх огноо :</h4>
							<div id="jira_datepickerRange" class="input-group input-daterange">
							    <input id="jira1_datepickerRange" type="text" class="form-control bg-light border-0 small border-bottom-primary" value="">
							    <div class="rangeDate">to</div>
							    <input id="jira2_datepickerRange" type="text" class="form-control bg-light border-0 small border-bottom-primary" value="">
							</div>
						</div>
						<div class="col-lg-4">
							<h4 class="small font-weight-bold">Алба :</h4>
							<select id="jira_department" class="form-control m-input" data-col-index="13">
								<option value="">Бүгд</option>
								<option value="10306">ДБА</option>
								<option value="10206">САА</option>
								<option value="10319">ТҮА</option>
							</select>
						</div>
						<div class="col-lg-4">
							<h4 class="small font-weight-bold">Домэйн ID :</h4>
							<input id="jira_domainID" type="text" class="form-control m-input" placeholder="" data-col-index="10">
						</div>
					</div><br><br>
					<div class="row">
						<div class="col-lg-4"></div>
						<div class="col-lg-4">
							<h4 class="small font-weight-bold">Хугацаандаа амжсан эсэх :</h4>
							<select id="jira_canTime" class="form-control m-input" data-col-index="12">
								<option value="">Бүгд</option>
								<option value="0">Тийм</option>
								<option value="1">Үгүй</option>
							</select>
						</div>
						<div class="col-lg-4">
							<h4 class="small font-weight-bold">Хугацаа шаардах эсэх :</h4>
							<select id="jira_requireTime" class="form-control m-input" data-col-index="1">
								<option value="">Бүгд</option>
								<option value="Тийм">Тийм</option>
								<option value="Үгүй">Үгүй</option>
							</select>
						</div>
					</div><br>
					<div class="row float-right">
						<div class="col-lg-12">
							<button id="m_clear" class="btn btn-secondary" type="button">
                                <span class="table_font"><i class="fas fa-close fa-sm"></i><span>Цэвэрлэх</span></span>
                            </button>
							&nbsp;&nbsp;
							<button id="m_search" class="btn btn-primary" type="button">
                                <span class="table_font"><i class="fas fa-search fa-sm"></i><span>&nbsp;Хайх</span></span>
                            </button>
						</div>
					</div>
				</div>
				<div class="card-body">
					<div class="table-responsive">
						<table class="table table-bordered" id="dataTableJira" width="100%" cellspacing="0">
							<thead>
								<tr>
									<th data-field="st_id">ID</th>
									<th data-field="st_kpi">KPI үзүүлэлт</th>
									<th data-field="st_stype">Төрөл</th>
									<th data-field="st_tmyo">Томёо</th>
									<th data-field="st_total_count">Нийт үүсэн жира</th>
									<th data-field="st_solived_count">Шийдвэрлэсэн жира</th>
									<th data-field="st_procent">Шийдсэн хувь</th>
								</tr>
							</thead>
							<tbody id="tableBodyJira">
								@include('jira.jirakpi_table')
							</tbody>
						</table>
						<hr>
						<div id="tableBodyJiraList">
							@include('jira.jiralist_table')
						</div>
					</div>
				</div>
			</div>
		</div>
	</div>
@endsection

@section('pagescript')
  	<script type="text/javascript" src="{{ asset('static/vendor/chart.js/Chart.min.js') }}"></script>
	<script type="text/javascript" src="{{ asset('static/js/chartjs.bundle.min.js') }}"></script>
	<script src="{{ asset('static/vendor/datatables/jquery.dataTables.min.js') }}"></script>
	<script src="{{ asset('static/vendor/datatables/dataTables.bootstrap4.min.js') }}"></script>
	<script src="{{ asset('static/js/bootstrap-datepicker.min.js') }}"></script>
	<script type="text/javascript" src="{{ asset('js/jira.js') }}"></script>
@endsection