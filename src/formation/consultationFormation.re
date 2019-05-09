open DecodeTraining;
open Config;
let styleInput = ReactDOMRe.Style.make(~paddingLeft="20px");
let styleImg = ReactDOMRe.Style.make(~width="150px", ~height="150px", ());
let data: string = "training.json";
let url_dev: string = "http://localhost:8080/";

let initialLevel = {idLevel: 0, grade: "", level: 0, nbECTS: 0, title: ""};
type state = DecodeTraining.trainingResponse;

type action =
  | Error(string)
  | Loaded(DecodeTraining.trainingResponse);

let containerConsult =
  ReactDOMRe.Style.make(~display="flex", ~flexDirection="row", ());

let component = ReasonReact.reducerComponent("consultationFormation");

let make = (_children, ~idFormation) => {
  let getTraining = self =>
    Js.Promise.(
      Fetch.fetchWithInit(
        url_back ++ "/trainings/" ++ idFormation,
        Fetch.RequestInit.make(
          ~method_=Get,
          ~headers=
            Fetch.HeadersInit.make({"Content-Type": "application/json"}),
          (),
        ),
      )
      |> Js.Promise.then_(Fetch.Response.json)
      |> Js.Promise.then_(json =>
           json
           |> DecodeTraining.decodeSingleResponse
           |> (
             result => self.ReasonReact.send(Loaded(result.singleTraining))
           )
           |> resolve
         )
    )
    |> ignore;
  {
    ...component,
    initialState: () => {
      idTraining: "",
      name: Some(""),
      description: Some(""),
      admLevel: Some([]),
      diplomaLevel: 0,
      expertise: Some(""),
      partTime: Some(false),
      logoPath: Some(""),
      link: Some(""),
      duration: 0,
      schoolName: "",
      schoolDescription: Some(""),
      schoolPostalcode: 0,
      schoolCity: Some(""),
      lowestScore: Some(0),
      highestScore: Some(0),
      averageScore: Some(0.0),
    },
    reducer: (action, _) =>
      switch (action) {
      | Error(_) => ReasonReact.NoUpdate
      | Loaded(result) =>
        ReasonReact.Update({
          idTraining: result.idTraining,
          name: result.name,
          description: result.description,
          admLevel: result.admLevel,
          diplomaLevel: result.diplomaLevel,
          expertise: result.expertise,
          partTime: result.partTime,
          logoPath: result.logoPath,
          link: result.link,
          duration: result.duration,
          schoolName: result.schoolName,
          schoolDescription: result.schoolDescription,
          schoolPostalcode: result.schoolPostalcode,
          schoolCity: result.schoolCity,
          lowestScore: result.lowestScore,
          highestScore: result.highestScore,
          averageScore: result.averageScore,
        })
      },
    didMount: self => getTraining(self),
    render: _self =>
      <div style=containerConsult>
        <div className="card align-middle mx-auto w-50 p-3 text-center">
          <div className="card-header">
            (ReasonReact.string("Consultation d'une formation"))
          </div>
          <div className="card-body">
            <div>
              <img
                style=styleImg
                src=(
                  switch (_self.state.logoPath) {
                  | Some(value) => value
                  | None => ""
                  }
                )
                alt="image formation"
              />
            </div>
            <div className="input-group mb-3">
              <label> (ReasonReact.string("Nom de la formation : ")) </label>
              <label>
                (
                  ReasonReact.string(
                    switch (_self.state.name) {
                    | Some(value) => value
                    | None => ""
                    },
                  )
                )
              </label>
            </div>
            <div className="input-group mb-3">
              <label> (ReasonReact.string("Description : ")) </label>
              <label>
                (
                  ReasonReact.string(
                    switch (_self.state.description) {
                    | Some(value) => value
                    | None => ""
                    },
                  )
                )
              </label>
            </div>
            <div className="input-group mb-3">
              <label> (ReasonReact.string("Niveau d'expertise : ")) </label>
              <label>
                (
                  ReasonReact.string(
                    switch (_self.state.expertise) {
                    | Some(value) => value
                    | None => ""
                    },
                  )
                )
              </label>
            </div>
            <div className="input-group mb-3">
              <label>
                (ReasonReact.string("Possible en alternance ?  "))
              </label>
              <label>
                (
                  ReasonReact.string(
                    switch (_self.state.partTime) {
                    | Some(_) => "Oui"
                    | None => "Non"
                    },
                  )
                )
              </label>
            </div>
            <div className="input-group mb-3">
              <label>
                (ReasonReact.string({js|Lien du site de l'école : |js}))
              </label>
              <a
                href=(
                  switch (_self.state.link) {
                  | Some(value) => value
                  | None => ""
                  }
                )>
                (ReasonReact.string(_self.state.schoolName))
              </a>
            </div>
            <div className="input-group mb-3">
              <label>
                (ReasonReact.string({js|Durée de la formation : |js}))
              </label>
              <label>
                (ReasonReact.string(string_of_int(_self.state.duration)))
              </label>
            </div>
            <div className="input-group mb-3">
              <label>
                (ReasonReact.string({js|Nom de l'école : |js}))
              </label>
              <label> (ReasonReact.string(_self.state.schoolName)) </label>
            </div>
            <div className="input-group mb-3">
              <label>
                (ReasonReact.string({js|Description de l'école : |js}))
              </label>
              <label>
                (
                  ReasonReact.string(
                    switch (_self.state.schoolDescription) {
                    | Some(value) => value
                    | None => ""
                    },
                  )
                )
              </label>
            </div>
            <div className="input-group mb-3">
              <label>
                (
                  ReasonReact.string(
                    {js|Code postal de la ville de l'école : |js},
                  )
                )
              </label>
              <label>
                (
                  ReasonReact.string(
                    string_of_int(_self.state.schoolPostalcode),
                  )
                )
              </label>
            </div>
            <div className="input-group mb-3">
              <label>
                (ReasonReact.string({js|Nom de la ville de l'école : |js}))
              </label>
              <label>
                (
                  ReasonReact.string(
                    switch (_self.state.schoolCity) {
                    | Some(value) => value
                    | None => ""
                    },
                  )
                )
              </label>
            </div>
          </div>
        </div>
        <div className="col-md-6"> <Notation idFormation /> </div>
      </div>,
  };
};