
open SessionUser;
type page =
  | Login
  | Register
  | Score;


module type Mapper = {
  let toPage: ReasonReact.Router.url => page;
  let toUrl: page => string;
};

module Mapper: Mapper = {
  let toPage = (url: ReasonReact.Router.url) =>
    switch(SessionUser.isConnected){
      | false => switch(url.path){
                  | ["register"] => Register
                  | ["login"] => Login
                  | _ => Login
                }
      |_ => switch(url.path){
                  | ["register"] => Register
                  | ["login"] => Login
                  | ["score"] => Score
                  | _ => Score
                }
    };


  let toUrl = page =>
    switch (page) {
    | Register => "register"
    | Score => "score"
    | Login => "login"
    };
};