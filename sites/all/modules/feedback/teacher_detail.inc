<?php
/**
   * Callback for theme form.
   *
   * @return theme;
   *   This contains two parameter
   *   @param feedback
   *     Name of theme.
   *   @param $user_detail
   *     Contains the Uid and User name of all users
   */
  function _user_detail() {
    // $detail = array(
    //   'Fname' => 'jitendra',
    //   'Lname' => 'jain',
    //   );
    // return theme('feedback', $detail);
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'user');
    $result = $query->execute();
    // Get all uid of all users
    $uids = array_keys($result['user']);
    // Get all User with respect their uid
    foreach ($uids as $key => $uid) {
      $user = user_load($uid);
      $user_detail[$user->uid] = array(
        'Uid' => $user->uid,
        'Uname' => $user->name,
        );
    }
    return theme('feedback', $user_detail);
  }
  /**
   * Theme function.
   *
   * @param $variable
   *   This variable is array of values.
   *
   * @return $output
   *   It is return theme output.
   */
  function theme_feedback($variable) {
    $output  = '<h2>Theme Page</h2>';
     unset($variable['theme_hook_original']);
    foreach ($variable as $key => $value) {
      $output .= '<div id = "mytheme" class = "mytheme">';
      $output .= '<br>1.' . $value['Uid'];
      $output .= '<br>2.' . $value['Uname'];
      $output .= '</div>';
    }
    return $output;
 }
