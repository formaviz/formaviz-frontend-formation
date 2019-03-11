type page =
  | Login
  | Register
  | Score;

module type Mapper = {
  let toPage: ReasonReact.Router.url => page;
  let toUrl: page => ReasonReact.Router.url;
};

module Mapper: Mapper = {
  let toPage: ReasonReact.Router.url => page =
    url =>
      switch url.path {
      | ["register"] => Register
      | ["login"] => Login
      | ["score"] => Score
      | _ => Register
      };
  let toUrl: page => ReasonReact.Router.url =
    page =>
      switch page {
      | Register => {path: ["register"], hash: "", search: ""}
      | Score => {path: ["score"], hash: "", search: ""}
      | Login => {path: ["login"], hash: "", search: ""}
      };
};