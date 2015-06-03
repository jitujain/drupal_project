<?php
/**
   * Callback function for form_alter hook.
   *
   * @return $student_names.
   *   This function return those students name whose are given the feedback to
   *   logged teacher.
   */
  function get_students_names() {
    global $user;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'teacher_feedback');
    $result = $query->execute();
    // Get all uid of all users
    if ( !empty($result)) {
      $nids = array_keys($result['node']);
      foreach ($nids as $key => $nid) {
        $nodes = node_load($nid);
        if ($user->uid == $nodes->field_teacher_ref['und'][0]['target_id']) {
          $students = user_load($nodes->uid);
          if (in_array('student', $students->roles)) {
            if (isset($students->name) && !empty($students->name)) {
              $student_names[$students->name] = $students->name;
            }
          }
        }
        else {
          $student_names[0] = 'select';
        }
      }
    }
    return $student_names;
  }
