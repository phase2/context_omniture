<?php
class context_omniture_reaction extends context_reaction {

  function options_form($context) {
    $settings = $this->fetch_from_context($context);
    $form = array(
      '#title' => 'Omniture Variables',
      '#type' => 'fieldset'
    );
    $form['variables'] = array(
      '#title' => 'Name',
      '#type' => 'textarea',
      '#description' => 'A list of variables to set for omniture each line should be of the form VARIABLE = VALUE.  tokens can be used for the value',
      '#default_value' => isset($settings['variables'])? $settings['variables'] : 0,
    );
    $form['token_help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('node'),

    );
    return $form;
  }

  function execute(&$vars) {
    $settings = array();
    $node = menu_get_object();
    foreach ($this->get_contexts() as $context) {
      if (isset($context->reactions[$this->plugin])) {
        $blob = $context->reactions[$this->plugin]['variables'];
        $blob = token_replace($blob, array("node" => $node));
        $lines = explode("\n", $blob);
        foreach($lines as $line) {
          if(preg_match("/^ *(.*?) *= *(.*?) *$/", $line, $match)) {
            $settings[$match[1]] = $match[2];
            
          }
        }
      }
    }
    dpm($settings);
  }

}
