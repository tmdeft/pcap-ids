<?php

namespace App\Http\Controllers;

use View;
use App\jira_kpi;
use Illuminate\Http\Request;

class JiraController extends Controller
{
	private $solved_easy;
	private $easy;
	private $procent_easy;
	private $solved_hard;
	private $hard;
	private $procent_hard;
	private $solved_normal_easy;
	private $normal_easy;
	private $procent_normal_easy;
	private $solved_normal_hard;
	private $normal_hard;
	private $procent_normal_hard;

    public function index(Request $request)
    {
        $jira_kpis = new JIRA_KPI();

    	if ($request->ajax()) {

			$firstDate = $request->input("firstDate");
			$secondDate = $request->input("secondDate");
			$department = $request->input("department");
			$domainID = $request->input("domainID");
			$canTime = $request->input("canTime");
			$requireTime = $request->input("requireTime");

            $jira_lists = $jira_kpis::select('*');

            if( !is_null($firstDate) && !is_null($secondDate) ) {
                $jira_lists = $jira_lists->whereBetween('created', [$firstDate, $secondDate]);
            }

            if( !is_null($department) ) {
                $jira_lists = $jira_lists->where('projectid','=',$department);
            }

            if( !is_null($domainID) ) {
                $jira_lists = $jira_lists->where('assignee','=', $domainID);
            }

            if( !is_null($canTime) ) {
                $jira_lists = $jira_lists->where('error','=', $canTime);
            }

            if( !is_null($requireTime) ) {
                $jira_lists = $jira_lists->where('type','like', $requireTime."%");
            }

            $this->calcKPI($jira_lists);

            $jira_listData = $jira_lists->orderBy('created', 'desc')->paginate(5);

            $list_view = View::make('jira.jiralist_table')->with('jira_lists', $jira_listData)->__toString();

            if( $request->has("firstDate") ) {

                $kpi_view = View::make('jira.jirakpi_table')->with('solved_easy', $this->solved_easy)
                                                   ->with('easy', $this->easy)
                                                   ->with('procent_easy', $this->procent_easy)
                                                   ->with('solved_hard', $this->solved_hard)
                                                   ->with('hard', $this->hard)
                                                   ->with('procent_hard', $this->procent_hard)
                                                   ->with('solved_normal_easy', $this->solved_normal_easy)
                                                   ->with('normal_easy', $this->normal_easy)
                                                   ->with('procent_normal_easy', $this->procent_normal_easy)
                                                   ->with('solved_normal_hard', $this->solved_normal_hard)
                                                   ->with('normal_hard', $this->normal_hard)
                                                   ->with('procent_normal_hard', $this->procent_normal_hard)->__toString();

                return response()->json(['kpi' => $kpi_view, 'list' => $list_view]);

    		} else {

                return response()->json(['list' => $list_view]);
    			// $jira_lists = $jira_kpis->orderBy('created', 'desc')->paginate(5);
                // return view('jira.jiralist_table', compact('jira_lists'));
    		}
        } else {

            $jira_kpis = new JIRA_KPI();
	        $this->calcKPI($jira_kpis);

	        $jira_lists = $jira_kpis->orderBy('created', 'desc')->paginate(5);
	        
	        return view('jira.jira')->with('solved_easy', $this->solved_easy)
									->with('easy', $this->easy)
									->with('procent_easy', $this->procent_easy)
									->with('solved_hard', $this->solved_hard)
									->with('hard', $this->hard)
									->with('procent_hard', $this->procent_hard)
									->with('solved_normal_easy', $this->solved_normal_easy)
									->with('normal_easy', $this->normal_easy)
									->with('procent_normal_easy', $this->procent_normal_easy)
									->with('solved_normal_hard', $this->solved_normal_hard)
									->with('normal_hard', $this->normal_hard)
									->with('procent_normal_hard', $this->procent_normal_hard)
									->with('jira_lists', $jira_lists);
        }
    }

    public function calcKPI($jira_lists)
    {
    	// Хугацаа шаардахгүй  ->  шийдвэрлэсэн JIRA
        $jira_kpis = clone $jira_lists;
        $this->solved_easy = $jira_kpis->where('MAXTIME','<=',8)->whereIn('status', ['10001-Шийдвэрлэсэн','10219-Хаагдсан'])->count();
        // Хугацаа шаардахгүй  ->  бүх JIRA
        $jira_kpis = clone $jira_lists;
        $this->easy = $jira_kpis->where('MAXTIME','<=',8)->count();
        // Хугацаа шаардахгүй  ->  Хувь
        $this->procent_easy = (int)floor(@($this->solved_easy*100/$this->easy)) === 0 ? 100 : (int)floor(@($this->solved_easy*100/$this->easy));


        // Хугацаа шаардагдах  ->  шийдвэрлэсэн JIRA
        $jira_kpis = clone $jira_lists;
        $this->solved_hard = $jira_kpis->where('MAXTIME','>',8)->whereIn('status', ['10001-Шийдвэрлэсэн','10219-Хаагдсан'])->count();
        
        // Хугацаа шаардагдах  ->  бүх JIRA
        $jira_kpis = clone $jira_lists;
        $this->hard = $jira_kpis->where('MAXTIME','>',8)->count();
        // Хугацаа шаардагдах  ->  Хувь
        $this->procent_hard = (int)floor(@($this->solved_hard*100/$this->hard))  === 0 ? 100 : (int)floor(@($this->solved_hard*100/$this->hard));


        // Стандарт хугацаандаа шийдвэрлэсэн JIRA (Хугацаа шаардагдахгүй)
        $jira_kpis = clone $jira_lists;
        $this->solved_normal_easy = $jira_kpis->where('MAXTIME','<=',8)->where('DIFF_TIME','<=','MAXTIME')->whereIn('status', ['10001-Шийдвэрлэсэн','10219-Хаагдсан'])->count();
        // Стандарт хугацаандаа шийдвэрлэсэн JIRA (Хугацаа шаардагдахгүй Бүх)
        $jira_kpis = clone $jira_lists;
        $this->normal_easy = $jira_kpis->where('MAXTIME','<=',8)->where('DIFF_TIME','<=','MAXTIME')->count();
        // Стандарт хугацаандаа шийдвэрлэсэн JIRA (Хувь)
        $this->procent_normal_easy = (int)floor(@($this->solved_normal_easy*100/$this->normal_easy))  === 0 ? 100 : (int)floor(@($this->solved_normal_easy*100/$this->normal_easy));
        

        // Стандарт хугацаандаа шийдвэрлэсэн JIRA (Хугацаа шаардагдах)
        $jira_kpis = clone $jira_lists;
        $this->solved_normal_hard = $jira_kpis->where('MAXTIME','>',8)->where('DIFF_TIME','<=','MAXTIME')->whereIn('status', ['10001-Шийдвэрлэсэн','10219-Хаагдсан'])->count();
        // Стандарт хугацаандаа шийдвэрлэсэн JIRA (Хугацаа шаардагдах Бүх)
        $jira_kpis = clone $jira_lists;
        $this->normal_hard = $jira_kpis->where('MAXTIME','>',8)->where('DIFF_TIME','<=','MAXTIME')->count();
        // Стандарт хугацаандаа шийдвэрлэсэн JIRA (Хувь)
        $this->procent_normal_hard = (int)floor(@($this->solved_normal_hard*100/$this->normal_hard))  === 0 ? 100 : (int)floor(@($this->solved_normal_hard*100/$this->normal_hard));
    }
}
