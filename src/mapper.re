type page =
  | Login
  | Register
  | Score
  | ConsultationFormation;

module type Mapper = {
  let toPage: ReasonReact.Router.url => page;
  let toUrl: page => string;
};

module Mapper: Mapper = {
  let toPage = (url: ReasonReact.Router.url) =>
    switch (url.path) {
    | ["register"] => Register
    | ["login"] => Login
    | ["score"] => Score
    | ["consult"] => ConsultationFormation
    | _ => ConsultationFormation
    };
  let toUrl = page =>
    switch (page) {
    | Register => "register"
    | Score => "score"
    | Login => "login"
    | ConsultationFormation => "consult"
    };
};
