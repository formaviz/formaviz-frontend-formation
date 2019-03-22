open DecodeTraining;
open Config;
let styleInput = ReactDOMRe.Style.make(~paddingLeft="20px");
let data: string = "trainings.json";

let initialLevel = {idLevel: 0, grade: "", level: 0, nbECTS: 0, title: ""};
type state = DecodeTraining.trainingType;

type action =
  | Nothing
  | Error(string)
  | Loaded(list(DecodeTraining.trainingType))
  | Success(list(DecodeTraining.trainingType))
  | ToTrainingView(string);

let component = ReasonReact.reducerComponent("listeFormation");

let make = _children => {
  let getTrainings = self =>
    Js.Promise.(
      Fetch.fetchWithInit(
        url_back ++ "/trainings",
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
           |> DecodeTraining.decodeResponse
           |> (result => self.ReasonReact.send(Loaded(result.trainings)))
           |> resolve
         )
    )
    |> ignore;
  {
    ...component,
    initialState: () => Nothing,
    reducer: (action, state) =>
      switch (action) {
      | Error(_) => ReasonReact.NoUpdate
      | Loaded(result) => ReasonReact.Update(Success(result))
      | ToTrainingView(value) =>
        ReasonReact.SideEffects(
          (_ => ReasonReact.Router.push("/consult/" ++ value)),
        )
      },
    didMount: self => getTrainings(self),
    render: _self =>
      switch (_self.state) {
      | Nothing => <div> (ReasonReact.string("Rien à afficher")) </div>
      | Error(_) =>
        <div>
          (ReasonReact.string("Erreur lors du chargement des données"))
        </div>
      | Loaded(_) =>
        <div> (ReasonReact.string("Chargement des données en cours")) </div>
      | Success(trainings) =>
        <div className="card align-middle mx-auto w-50 p-3 text-center">
          <div className="card-header">
            (ReasonReact.string("Liste des formations"))
          </div>
          <div className="card-body">
            <ul>
              (
                trainings
                |> List.map(trainings =>
                     <li
                       key=trainings.training.idTraining
                       onClick=(
                         _ =>
                           _self.send(
                             ToTrainingView(trainings.training.idTraining),
                           )
                       )>
                       <div className="input-group">
                         <label>
                           (
                             ReasonReact.string(
                               switch (trainings.training.name) {
                               | Some(value) => value
                               | None => "Aucun nom"
                               },
                             )
                           )
                         </label>
                       </div>
                       <div className="input-group">
                         <label> (ReasonReact.string("Pire note : ")) </label>
                         <label>
                           (
                             ReasonReact.string(
                               string_of_int(
                                 switch (trainings.training.lowestScore) {
                                 | Some(value) => value
                                 | None => 0
                                 },
                               ),
                             )
                           )
                         </label>
                       </div>
                       <div className="input-group">
                         <label>
                           (ReasonReact.string("Meilleure note : "))
                         </label>
                         <label>
                           (
                             ReasonReact.string(
                               string_of_int(
                                 switch (trainings.training.highestScore) {
                                 | Some(value) => value
                                 | None => 0
                                 },
                               ),
                             )
                           )
                         </label>
                       </div>
                       <div className="input-group">
                         <label> (ReasonReact.string("Moyenne : ")) </label>
                         <label>
                           (
                             ReasonReact.string(
                               string_of_float(
                                 switch (trainings.training.averageScore) {
                                 | Some(value) => value
                                 | None => 0.0
                                 },
                               ),
                             )
                           )
                         </label>
                       </div>
                     </li>
                   )
                |> Array.of_list
                |> ReasonReact.array
              )
            </ul>
          </div>
        </div>
      },
  };
};