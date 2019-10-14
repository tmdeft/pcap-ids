<table class="table table-bordered" id="dataTableJiraList" width="100%" cellspacing="0">
	<thead>
		<tr>
			<th data-field="PROJECTNAME">Прожект</th>
			<th data-field="TYPE">Хугацаа шаардах эсэх</th>
			<th class="hider" data-field="TYPENAME">Төрөл</th>
			<th data-field="COMPNAME">Бүрэлдхүүн</th>
			<th data-field="JIRANUM">Дугаар</th>
			<th data-field="STATUS">Төлөв</th>
			<th data-field="ASSIGNEENAME">Хариуцах ажилтан</th>
			<th data-field="CREATED">Үүсгэсэн огноо</th>
			<th data-field="L_RESOLUTIONDATE">Шийдэгдсэн огноо</th>
			<th data-field="DIFF_TIME">Зарцуулсан хугацаа</th>
			<th class="hider" data-field="MAXTIME">Стандарт хугацаа</th>
			<th class="hider" data-field="ASSIGNEE">Хариуцах ажилтан id</th>
		</tr>
	</thead>
	<tbody id="tableBodyJiraList">
		@foreach ($jira_lists as $jira_list)
			@if( $jira_list->error == 1 )
				<tr class="error_row">
			@else
				<tr>
			@endif
				<td>{{ $jira_list->projectname }}</td>
				<td>{{ $jira_list->type }}</td>
				<td>{{ $jira_list->typename }}</td>
				<td>{{ $jira_list->compname }}</td>
				<td>{{ $jira_list->jiranum }}</td>
				<td>{{ $jira_list->status }}</td>
				<td>{{ $jira_list->assigneename }}</td>
				<td>{{ $jira_list->created }}</td>
				<td>{{ $jira_list->l_resolutiondate }}</td>
				<td>{{ $jira_list->diff_time }}</td>
				<td>{{ $jira_list->maxtime }}</td>
				<td>{{ $jira_list->assignee }}</td>
			</tr>
		@endforeach
	</tbody>
</table>

{{ $jira_lists->render() }}