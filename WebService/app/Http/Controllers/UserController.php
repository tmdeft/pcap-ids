<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\User;
use App\Role;
use App\RoleAndUser;

class UserController extends Controller {

	public function index()
    {

        return view('dashboard');
    }

    public function roles()
    {
    	$users = User::select('id','givenname')->orderBy('givenname')->get();
    	$roles = Role::all();
    	$roleanduser = RoleAndUser::select('role_and_user.id', 'users.givenname', 'role.name')
    							  ->join('users', 'role_and_user.user_id', '=', 'users.id')
    							  ->join('role', 'role_and_user.role_id', '=', 'role.id')
    							  ->orderBy('users.givenname')
    							  ->get();

    	return view('user.roles')->with('users', $users)
    							 ->with('roles', $roles)
    							 ->with('roleandusers', $roleanduser);
    }

    public function addrole(Request $request)
    {
    	$role = $request->role;
    	$description = $request->roleDesc;

    	$checkRole = Role::where('name', '=', $role)->first();

    	if ($checkRole === null) {

			$newrole = new Role;
			$newrole->name = $role;
			$newrole->description = $description;
			$newrole->save();

			return response()->json(['status' => 'success', 'role' => $role, 'id' => $newrole->id, 'description' => $description]);
    	} else {
			return response()->json(['status' => 'exist', 'role' => $role, 'id' => $newrole->id, 'description' => $description]);
    	}

    }

    public function grantRole(Request $request)
    {
    	$userID = $request->userID;
    	$roleID = $request->roleID;

    	$user = User::where('id', '=', $userID)->first();
    	$role = Role::where('id', '=', $roleID)->first();
    	$roleanduser = RoleAndUser::where([['user_id', '=', $userID],['role_id', '=', $roleID]])->first();

    	if ($user != null && $role != null && $roleanduser === null) {

	    	$newRoleAndUser = new RoleAndUser;
	    	$newRoleAndUser->user_id = $userID;
	    	$newRoleAndUser->role_id = $roleID;
	    	$newRoleAndUser->save();

    		return response()->json(['status' => "success", 'id' => $newRoleAndUser->id]);
    	} else {

    		return response()->json(['status' => "error"]);
    	}
    }

    public function revokeRole(Request $request)
    {
    	$roleAndUserID = $request->roleAndUserID;

    	$roleanduser = RoleAndUser::where('id', '=', $roleAndUserID)->first();

    	if ( $roleanduser != null ) {

    		$roleanduser->delete();
    		return response()->json(['status' => "success"]);
    	}

    	return response()->json(['status' => "error"]);
    }
}