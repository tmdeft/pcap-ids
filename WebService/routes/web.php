<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

// Route::get('/', function () {
//     return view('welcome');
// });
Route::get('/', function(){
    return view('dashboard');
});
Route::get('/dashboard', function(){
    return view('dashboard');
});
Route::get('/app',function(){
    return view('application');
});
Route::get('/doslog',function(){
    $data = DB::table('dosLog')->get();
    return view('doslog', ['data' => $data]);
});

Route::get('jiras', 'JiraController@index')->name('jiras');
