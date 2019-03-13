open DecodeTraining;
let styleInput = ReactDOMRe.Style.make(~paddingLeft="20px");
let data: string = "trainings.json";
let url_dev: string = "http://localhost:8080/";

let initialLevel = {idLevel: 0, grade: "", level: 0, nbEcts: 0, titre: ""};
type state = list(DecodeTraining.trainingResponse);

type action =
  | Nothing
  | Error(string)
  | Loaded(state)
  | Success(state)
  | ToTrainingView(string);

let component = ReasonReact.reducerComponent("listeFormation");

let make = _children => {
  let getTrainings = self => {
    let payload = Js.Dict.empty();
    Js.Promise.(
      Fetch.fetchWithInit(
        url_dev ++ data,
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
           |> DecodeTraining.decodeTrainings
           |> (result => self.ReasonReact.send(Loaded(result)))
           |> resolve
         )
    )
    |> ignore;
  };
  {
    ...component,
    initialState: () => {
      Nothing;
    },
    reducer: (action, state) =>
      switch (action) {
      | Error(string) => ReasonReact.NoUpdate
      | Loaded(result) => ReasonReact.Update(Success(result))
      | ToTrainingView(value) =>
        ReasonReact.SideEffects(
          _ => ReasonReact.Router.push("/consult/" ++ value),
        )
      },
    didMount: self => getTrainings(self),
    render: _self =>
      switch (_self.state) {
      | Nothing => <div> {ReasonReact.string("Rien à afficher")} </div>
      | Error(string) =>
        <div>
          {ReasonReact.string("Erreur lors du chargement des données")}
        </div>
      | Loaded(state) =>
        <div> {ReasonReact.string("Chargement des données en cours")} </div>
      | Success(trainings) =>
        <div className="card align-middle mx-auto w-50 p-3 text-center">
          <div className="card-header">
            {ReasonReact.string("Liste des formations")}
          </div>
          <div className="card-body">
            <ul>
              {trainings
               |> List.map(trainings =>
                    <li
                      key={trainings.idFormation}
                      onClick={_ =>
                        _self.send(ToTrainingView(trainings.idFormation))
                      }>
                      <div className="input-group">
                        <label>
                          {ReasonReact.string(
                             switch (trainings.name) {
                             | Some(value) => value
                             | None => "Aucun nom"
                             },
                           )}
                        </label>
                      </div>
                      <div className="input-group">
                        <label> {ReasonReact.string("Pire note : ")} </label>
                        <label>
                          {ReasonReact.string(
                             string_of_int(
                               switch (trainings.lowestScore) {
                               | Some(value) => value
                               | None => 0
                               },
                             ),
                           )}
                        </label>
                      </div>
                      <div className="input-group">
                        <label>
                          {ReasonReact.string("Meilleure note : ")}
                        </label>
                        <label>
                          {ReasonReact.string(
                             string_of_int(
                               switch (trainings.highestScore) {
                               | Some(value) => value
                               | None => 0
                               },
                             ),
                           )}
                        </label>
                      </div>
                      <div className="input-group">
                        <label> {ReasonReact.string("Moyenne : ")} </label>
                        <label>
                          {ReasonReact.string(
                             string_of_float(
                               switch (trainings.averageScore) {
                               | Some(value) => value
                               | None => 0.0
                               },
                             ),
                           )}
                        </label>
                      </div>
                    </li>
                  )
               |> Array.of_list
               |> ReasonReact.array}
            </ul>
          </div>
        </div>
      },
  };
};