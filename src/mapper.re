type page =
  | Login
  | Register
  | ConsultationFormation(string)
  | ListeFormation
  | CreateTraining;

module type Mapper = {
  let toPage: ReasonReact.Router.url => page;
  let toUrl: page => ReasonReact.Router.url;
};

module Mapper: Mapper = {
  let toPage: ReasonReact.Router.url => page =
    url =>
      switch (url.path) {
      | ["register"] => Register
      | ["login"] => Login
      | ["consult", id] => ConsultationFormation(id)
      | ["liste"] => ListeFormation
      | ["createTraining"] => CreateTraining
      | _ => Register
      };

  let toUrl: page => ReasonReact.Router.url =
    page =>
      switch (page) {
      | Register => {path: ["register"], hash: "", search: ""}
      | Login => {path: ["login"], hash: "", search: ""}
      | ConsultationFormation(id) => {
          path: ["consult", id],
          hash: "",
          search: "",
        }
      | ListeFormation => {path: ["liste"], hash: "", search: ""}
      | CreateTraining => {path: ["createTraining"], hash: "", search: ""}
      };
};
