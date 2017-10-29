<?php
    namespace App\Http\Controllers;

    use Illuminate\Support\Facades\DB;
    use App\Http\Controllers\Controller;
    use Illuminate\Database\Eloquent\Model;

    use View;
    use Response;
    use json;
    class TestController extends Controller{
      public function index(){
          return view('test.index');
      }
      public function test(){
          return view('dashboard.index');
      }
      public function summary(){
          return view('dashboard.chart');
      }
      public function getData(){
        $datas = DB::table('summaryTable')->where('ID','1')->get();
        $collection = collect($datas);
        $res = $collection->toJson();
        return $res;
      }
    }
?>
