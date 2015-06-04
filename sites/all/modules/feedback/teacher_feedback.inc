<?php
   /**
   * Callback for feedback_menu hook.
   *
   * @param $form.
   * @param $form_state.
   */
  function form_feed_form($form, &$form_state) {
    // Check which radio button is set.
    if (isset($form_state['values']['Edit'])) {
      // Get the selected value from drop-down.
      $teacher_select = $form_state['values']['Edit'];
      // Call the  function get_prevalues().
      $prevalues = get_prevalues($teacher_select);
    }
    // Form elements.
    // Radio buttons with option Add and Edit.
    $form['choice'] = array(
      '#type' => 'radios',
      '#title' => t('select yr choice'),
      '#default_value' => 0,
      '#values' => array( 0 => 'N', 1 => 'Y'),
      '#options' => array(
      t('Add'),
      t('Edit'),
      )
    );
    // Drop-down list.
    // Render when Add radio button is selected.
    // For option list call the get_teacher_names().
    $form['Add'] = array(
      '#type' => 'select',
      '#title' => t('Choose a value'),
      '#id' => 'names',
      '#options' => get_teacher_names(),
      '#states' => array(
        'visible' => array(
        ':input[name="choice"]' => array('value' => '0'),
        ),
      ),
    );
    // Drop-down list.
    // Render when Edit radio button is selected.
    // For option list call the get_feedback_teacher_names().
    // Ajax is apply.
    $form['Edit'] = array(
      '#type' => 'select',
      '#title' => t('Choose a value'),
      '#id' => 'names1',
      '#options' => get_feedback_teacher_names(),
      '#states' => array(
        'visible' => array(
        ':input[name="choice"]' => array('value' => '1'),
        ),
      ),
      '#ajax' => array(
        'callback' => 'add_prefill_value',
        'wrapper' => 'teacher_rating_wrapper',
        'effect' => 'fade',
        'method' => 'html',
      ),
    );
    // Wrapper for ajax.
    $form['teacher_rating_wrapper'] = array(
      '#prefix' => '<div id="teacher_rating_wrapper">',
      '#suffix' => '</div>',
      '#type' => 'container',
    );

    // Following code is about the rating fields.
    // This code show the star on the form.

    // For knowledge field.
    // Add 1--5 as class for selector.
    $form['kstar'] = array(
      '#prefix' => '<div id="Knowledge-rating-star" class = "divspace">
      Knowledge<br>
      <span class = "whitestar spanspace knowledge 1"></span>
      <span class = "whitestar spanspace knowledge 2"></span>
      <span class = "whitestar spanspace knowledge 3"></span>
      <span class = "whitestar spanspace knowledge 4"></span>
      <span class = "whitestar spanspace knowledge 5"></span>',
      '#suffix' => '</div>',
      '#type' => 'container',
    );
    // For attitude field.
    // Add 1--5 as class for selector.
    $form['astar'] = array(
      '#prefix' => '<div id="Attitude-rating-star" class = "divspace">
      Attitude<br>
      <span class = "whitestar spanspace attitude 1"></span>
      <span class = "whitestar spanspace attitude 2"></span>
      <span class = "whitestar spanspace attitude 3"></span>
      <span class = "whitestar spanspace attitude 4"></span>
      <span class = "whitestar spanspace attitude 5"></span>',
      '#suffix' => '</div>',
      '#type' => 'container',
    );
    // For friendliness field.
    // Add 1--5 as class for selector.
    $form['fstar'] = array(
      '#prefix' => '<div id="Friendliness-rating-star" class = "divspace">
      Friendliness<br>
      <span class = "whitestar spanspace friendliness 1"></span>
      <span class = "whitestar spanspace friendliness 2"></span>
      <span class = "whitestar spanspace friendliness 3"></span>
      <span class = "whitestar spanspace friendliness 4"></span>
      <span class = "whitestar spanspace friendliness 5"></span>',
      '#suffix' => '</div>',
      '#type' => 'container',
    );
    // Hidden field for knowledge .
    // Values are passed for this field is equal to no. of selected star.
    $form['teacher_rating_wrapper']['Knowledge'] = array(
      '#type' => 'hidden',
      '#value' => isset($prevalues['Knowledge']) ? $prevalues['Knowledge'] : '',
    );
    // Hidden field for attitude .
    // Values are passed for this field is equal to no. of selected star.
    $form['teacher_rating_wrapper']['Attitude'] = array(
      '#type' => 'hidden',
      '#value' => isset($prevalues['Attitude']) ? $prevalues['Attitude'] : '',
    );
    // Hidden field for friendliness .
    // Values are passed for this field is equal to no. of selected star.
    $form['teacher_rating_wrapper']['Friendliness'] = array(
      '#type' => 'hidden',
      '#value' => isset($prevalues['Friendliness']) ? $prevalues['Friendliness'] : '',
    );
    //Adding submit button
    $form['submit_button'] = array(
      '#type'  => 'submit',
      '#value' => t('Click Here!'),
    );
  return $form;
  }
  /**
   * Callback wrapper function.
   *
   * @return $form['teacher_rating_wrapper'].
   */
  function add_prefill_value($form, &$form_state) {

    if (isset($form_state['values']['Edit'])) {
      $form_state['rebuild'] = TRUE;
      return $form['teacher_rating_wrapper'];
    }
  }
  /**
   * Callback function get_prevalues().
   *
   * @param $teacher_select.
   *   This is selected teacher name from drop drow.
   *
   * @return $prefillvalues.
   *   This is array of pre rating values.
   */
  function get_prevalues($teacher_select) {
    global $user;
    // Build an EntityFieldQuery for a entity type node.
    // Machine name of content_type is teacher_feedback.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'teacher_feedback');
    $result = $query->execute();
    // Get all node nids.
    $nids = array_keys($result['node']);
    // Load a node on their nid.
    foreach ($nids as $key => $nid) {
      $nodes = node_load($nid);
      // Check whether logged in user uid is equals to node uid.
      if ($user->uid == $nodes->uid) {
        // Get the teacher reference.
        $teacher_ref=$nodes->field_teacher_ref['und'][0]['target_id'];
        // Check whether paramter is equal to teacher_reference
        if ($teacher_select == $teacher_ref) {
          // If condition true then assign the pre values in the array keys.
          $prefillvalues = array(
            'Knowledge' => $nodes->field_knowledge['und'][0]['value'],
            'Attitude' => $nodes->field_attitude['und'][0]['value'],
            'Friendliness' => $nodes->field_friendliness['und'][0]['value']);
        }
      }
    }
    return $prefillvalues;
  }

  /**
   * Validate function for form submission.
   *
   */
  function form_feed_form_validate($form, &$form_state) {
    // Check whether field are empty or not.
    if ($form_state['input']['Knowledge'] == "" ||
        $form_state['input']['Attitude'] == "" ||
        $form_state['input']['Friendliness'] == "") {
      form_set_error('fnamdse', t('Please Give Rating'));
    }
    elseif ($form_state['input']['Knowledge'] <0 ||
            $form_state['input']['Knowledge'] >5 ) {
      form_set_error('fnasdme', t('Rating must be betwwn 0 t0 5'));
    }
    elseif ($form_state['input']['Attitude'] <0 ||
            $form_state['input']['Attitude'] >5 ) {
      form_set_error('fnasdme', t('Rating must be betwwn 0 t0 5'));
    }
    elseif ($form_state['input']['Friendliness'] <0 ||
            $form_state['input']['Friendliness'] >5 ) {
      form_set_error('fnasdme', t('Rating must be betwwn 0 t0 5'));
    }

  }

  /**
   * Callback function for Add radio button.
   *
   * @return $teacher_names.
   *   An array of teacher names.
   *
   */
  function get_teacher_names() {
    // build the EntityFieldQuery for entity_type user.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'user');
    $result = $query->execute();
    // Get all uid of all users
    $uids = array_keys($result['user']);
    // Get all User with respect their uid
    foreach ($uids as $key => $uid) {
      $user = user_load($uid);
      // Select only those user who have 'teacher' as role
       if (in_array('teacher', $user->roles)) {
        if (isset($user->name) && !empty($user->name)) {
          $teacher_names[$uid] = $user->name;
        }
      }
    }
    $feedback_teacher[]=get_feedback_teacher_names();
    if (!empty(get_feedback_teacher_names())) {
      // @return array difference of two arryas
      // first array is all teachers and second one is those teachers for which
      // feedback is given by the current user.
      return array_diff($teacher_names, get_feedback_teacher_names());
    }
    else{
      return $teacher_names;
    }
  }
  /**
   * Callback for Edit radio buttton.
   *
   * @return $feed_teacher_names;
   *   An array of teacher names for which feedback is given.
   */
  function get_feedback_teacher_names() {
    global $user;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'teacher_feedback');
    $result = $query->execute();
    // Get all uid of all users.
    if (!empty($result)) {
    $nids = array_keys($result['node']);
    foreach ($nids as $key => $nid) {
      $nodes = node_load($nid);
      if ($user->uid==$nodes->uid) {
        $authors = user_load($nodes->field_teacher_ref['und'][0]['target_id']);
        if (in_array('teacher', $authors->roles)) {
          if (isset($authors->name) && !empty($authors->name)) {
            $feed_teacher_names[$authors->uid] = $authors->name;
          }
        }
      }
      else {
        $feed_teacher_names[0] ='select';
      }
    }
    return $feed_teacher_names;
    }

  }

  /**
   * Form submit function.
   *
   */

  function form_feed_form_submit($form, &$form_state) {
    global $user;
    $current_nid;
    // This code is use to get current node nid.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'teacher_feedback');
    $result = $query->execute();
    $nids = array_keys($result['node']);
    foreach ($nids as $key => $nid) {
      $nodes = node_load($nid);
      if ($user->uid==$nodes->uid) {
        $teacher_ref=$nodes->field_teacher_ref['und'][0]['target_id'];
        $teacher_select = $form_state['values']['Edit'];
        if ($teacher_select == $teacher_ref) {
          $current_nid = $nodes->nid;
        }
      }
    }
    // If Add radio is click.
    if ($form_state['values']['choice'] == 0) {
      // Create a new node.
      $node = new stdClass();
      $node->language = LANGUAGE_NONE;
      $node->type = 'teacher_feedback';
      node_object_prepare($node);
      $node->uid = $user->uid;
      $node->status = 1;
      $node->field_teacher_ref[$node->language][0]['target_id'] = $form_state['values']['Add'];
    }
    // If Edit radio button is click.
    if ($form_state['values']['choice'] == 1) {
      // Load current node on the basis if current nid.
      $node = node_load($current_nid);
      $node->field_teacher_ref[$node->language][0]['target_id'] = $form_state['values']['Edit'];
    }
    // Set the values in node fields.
    $node->title = 'Feedback is save on ' . date('c');
    $node->field_attitude[$node->language][0]['value'] = $form_state['input']['Attitude'];
    $node->field_knowledge[$node->language][0]['value'] = $form_state['input']['Knowledge'];
    $node->field_friendliness[$node->language][0]['value'] = $form_state['input']['Friendliness'];
    node_save($node);
    drupal_set_message("You have registered successfully.");
  }
