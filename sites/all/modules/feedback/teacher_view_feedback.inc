<?php
  /**
   * Callback for view feedback form for teacher.
   */
  function student_feedback_form($form, &$form_state) {
    // Check whether drop down selected or not..
    if (isset($form_state['values']['selectlist'])) {
      // Get the selected value from drop-down.
      $student_select = $form_state['values']['selectlist'];
      // Call the  function get_values().
      $given_rating = get_values($student_select);
    }
    // Drop down form element.
    $form['selectlist'] = array(
      '#type' => 'select',
      '#title' => t('Choose a value'),
      '#id' => 'names1',
      '#options' => get_students_uid(),
      '#ajax' => array(
        'callback' => 'show_values',
        'wrapper' => 'given_rating_wrapper',
        'effect' => 'fade',
        'method' => 'replace',
      ),
    );
    // Container which a div of id given_rating_wrapper.
    $form['given'] = array(
      '#tree' => TRUE,
      '#type' => 'container',
      '#prefix' => '<div id="given_rating_wrapper">',
      '#suffix' => '</div>',
    );
    if (isset($form_state['values']['selectlist']) && !empty($form_state['values']['selectlist'])) {
      $form['given']['Attitude'] = array(
        '#type' => 'textfield',
        '#title' => 'Attitude',
        '#value' => $given_rating['Attitude']
      );
      $form['given']['Knowledge'] = array(
        '#type' => 'textfield',
        '#title' => 'Knowledge',
        '#value' => $given_rating['Knowledge']
      );
      $form['given']['Friendliness'] = array(
        '#type' => 'textfield',
        '#title' => 'Friendliness',
        '#value' => $given_rating['Friendliness']
      );
    }
    return $form;
  }

  /**
   * Callback for block.
   *
   * @return avg.
   *   Average rating for current logged in teacher.
   */
  function get_avg() {
    global $user;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'teacher_feedback');
    $result = $query->execute();
    // Get all uid of all users.
    $sum = 0;
    $count = 0;
    if (!empty($result)) {
      $nids = array_keys($result['node']);
      foreach ($nids as $key => $nid) {
        $nodes = node_load($nid);
          if ($user->uid == $nodes->field_teacher_ref['und'][0]['target_id']) {
            $students = user_load($nodes->uid);
            // Numbers of students whose are given the feedback to current logged in teacher.
            $count++;
            // Perform calculation and get sum of all ratings.
            $sum += $nodes->field_attitude['und'][0]['value'] + $nodes->field_knowledge['und'][0]['value'] + $nodes->field_friendliness['und'][0]['value'];
          }
      }
      // Get average.
      if ($count != 0) {
        $avg = '' . $sum / (3 * $count);
      }
      else {
        $avg = 'No one give rating  you yet' ;
      }
    }
    return $avg;
  }
   /**
   * Callback function get_values().
   *
   * @param $student_select.
   *   This is selected student name from drop drow.
   *
   * @return $rating_values.
   *   This is array of pre rating values.
   */
  function get_values($student_select) {
    global $user;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'teacher_feedback');
    $result = $query->execute();
    //get all uid of all users
    if (!empty($result)) {
      $nids = array_keys($result['node']);
      foreach ($nids as $key => $nid) {
        $nodes = node_load($nid);
          if ($user->uid == $nodes->field_teacher_ref['und'][0]['target_id']) {
            $students = user_load($nodes->uid);
            if ($students->uid == $student_select) {
              $rating_values = array(
                'Knowledge' => $nodes->field_knowledge['und'][0]['value'],
                'Attitude' => $nodes->field_attitude['und'][0]['value'],
                'Friendliness' => $nodes->field_friendliness['und'][0]['value']);
            }
          }
      }

    }
    return $rating_values;
  }
  /**
   * Ajax Wrapping function.
   */
  function show_values($form, &$form_state) {
         return $form['given'];
  }
  /**
   * Callback function for student_feedback_form.
   *
   * @return $student_names.
   *   This function return those students name whose are given the feedback to
   *   logged teacher.
   */
  function get_students_uid() {
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
              $student_names[$students->uid] = $students->name;
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
