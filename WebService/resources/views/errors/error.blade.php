@extends('layout.__back')

@section('body')

	@isset( $error_code)
		<br>
		<br>
		<div class="text-center">
            <div class="error mx-auto" data-text="{{ $error_code }}">{{ $error_code }}</div>
            <p class="lead text-gray-800 mb-5">Page Not Found</p>
            <p class="text-lg text-gray-500 mb-0"><b>Or you don't have access to resource</b></p>
          </div>
	@endisset

@endsection