open DecodeTraining;

let styleInput = ReactDOMRe.Style.make(~paddingLeft="20px");

let url_dev: string = "http://localhost:8080/";

type state = {
  name: string,
  description: string,
  admLevel: list(int),
  diplomaLevel: int,
  expertise: string,
  partTime: bool,
  logoPath: string,
  link: string,
  duration: string,
  schoolName: string,
  schoolDescription: string,
  schoolPostalCode: string,
  schoolCity: string,
  lowestScore: int,
  highestScore: int,
  averageScore: float,
  listLevel: list(DecodeTraining.levelResponse),
  error: string,
};

type action =
  | UpdateNameField(string)
  | UpdateDescriptionField(string)
  | UpdateExpertiseField(string)
  | UpdatePartTimeField(bool)
  | UpdateLogoPath(string)
  | UpdateLinkField(string)
  | UpdateDurationField(string)
  | UpdateSchoolNameField(string)
  | UpdateSchoolDescriptionField(string)
  | UpdateSchoolPostalCodeField(string)
  | UpdateSchoolCityField(string)
  | Loaded(list(DecodeTraining.levelResponse))
  | CreateTraining
  | Created
  | Error(string);

let select_partTime = (event, self) =>
  switch (ReactEvent.Form.target(event)##value) {
  | "true" => self.ReasonReact.send(UpdatePartTimeField(true))
  | "false" => self.send(UpdatePartTimeField(false))
  | _ => self.send(UpdatePartTimeField(false))
  };

let string_of_bool = value => value ? "true" : "false";

let handleChange = event => Js.log(ReactEvent.Form.target(event)##value);

let component = ReasonReact.reducerComponent("createTraining");

let make = _children => {
  let getLevel = self =>
    Js.Promise.(
      Fetch.fetchWithInit(
        Config.url_back ++ "/levels",
        Fetch.RequestInit.make(
          ~method_=Get,
          ~headers=
            Fetch.HeadersInit.make({
              "Content-Type": "application/json",
              "Authorization": "Bearer " ++ SessionUser.getToken,
            }),
          (),
        ),
      )
      |> Js.Promise.then_(Fetch.Response.json)
      |> Js.Promise.then_(json =>
           json
           |> DecodeTraining.decodeLevelResponse
           |> (result => self.ReasonReact.send(Loaded(result.levels)))
           |> resolve
         )
    )
    |> ignore;
  let sendTraining = state => {
    let payload = Js.Dict.empty();
    Js.Dict.set(payload, "name", Js.Json.string(state.name));
    Js.Dict.set(payload, "description", Js.Json.string(state.description));
    Js.Dict.set(payload, "admLevel", Js.Json.array([||]));
    Js.Dict.set(
      payload,
      "diplomaLevel",
      Json.Encode.int(state.diplomaLevel),
    );
    Js.Dict.set(payload, "expertise", Js.Json.string(state.expertise));
    Js.Dict.set(payload, "partTime", Js.Json.boolean(state.partTime));
    Js.Dict.set(payload, "logoPath", Js.Json.string(state.logoPath));
    Js.Dict.set(payload, "link", Js.Json.string(state.link));
    Js.Dict.set(
      payload,
      "duration",
      Json.Encode.int(int_of_string(state.duration)),
    );
    Js.Dict.set(
      payload,
      "school",
      Json.Encode.(
        object_([
          ("name", string(state.schoolName)),
          ("description", string(state.schoolDescription)),
          ("cp", string(state.schoolPostalCode)),
          ("city", string(state.schoolCity)),
        ])
      ),
    );
    Js.Dict.set(payload, "lowestScore", Json.Encode.int(state.lowestScore));
    Js.Dict.set(
      payload,
      "highestScore",
      Json.Encode.int(state.highestScore),
    );
    Js.Dict.set(
      payload,
      "averageScore",
      Json.Encode.float(state.averageScore),
    );
    Js.Promise.(
      Fetch.fetchWithInit(
        Config.url_back ++ "/trainings",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=
            Fetch.BodyInit.make(
              Js.Json.stringify(Js.Json.object_(payload)),
            ),
          ~headers=
            Fetch.HeadersInit.make({
              "Content-Type": "application/json",
              "Authorization": "Bearer " ++ SessionUser.getToken,
            }),
          (),
        ),
      )
      |> then_(Fetch.Response.json)
      |> then_(json =>
           json
           |> DecodeRating.decodeResponseSend
           |> (resp => Some(resp) |> resolve)
         )
    );
  };
  {
    ...component,
    initialState: () => {
      name: "",
      description: "",
      admLevel: [],
      diplomaLevel: 1,
      expertise: "",
      partTime: false,
      logoPath: "",
      link: "",
      duration: "",
      schoolName: "",
      schoolDescription: "",
      schoolPostalCode: "",
      schoolCity: "",
      lowestScore: 0,
      highestScore: 0,
      averageScore: 0.0,
      listLevel: [],
      error: "",
    },
    reducer: (action, state) =>
      switch (action) {
      | UpdateNameField(name) => ReasonReact.Update({...state, name})
      | UpdateDescriptionField(description) =>
        ReasonReact.Update({...state, description})
      | UpdateExpertiseField(expertise) =>
        ReasonReact.Update({...state, expertise})
      | UpdatePartTimeField(partTime) =>
        ReasonReact.Update({...state, partTime})
      | UpdateLogoPath(logoPath) => ReasonReact.Update({...state, logoPath})
      | UpdateLinkField(link) => ReasonReact.Update({...state, link})
      | UpdateDurationField(duration) =>
        ReasonReact.Update({...state, duration})
      | UpdateSchoolNameField(schoolName) =>
        ReasonReact.Update({...state, schoolName})
      | UpdateSchoolDescriptionField(schoolDescription) =>
        ReasonReact.Update({...state, schoolDescription})
      | UpdateSchoolPostalCodeField(schoolPostalCode) =>
        ReasonReact.Update({...state, schoolPostalCode})
      | UpdateSchoolCityField(schoolCity) =>
        ReasonReact.Update({...state, schoolCity})
      | Loaded(listLevel) => ReasonReact.Update({...state, listLevel})
      | Created =>
        ReasonReact.SideEffects((_self => ReasonReact.Router.push("liste")))
      | Error(value) => ReasonReact.NoUpdate
      | CreateTraining =>
        ReasonReact.UpdateWithSideEffects(
          state,
          (
            self =>
              Js.Promise.(
                sendTraining(state)
                |> then_(result =>
                     switch (result) {
                     | Some(_) => resolve(self.send(Created))
                     | None =>
                       resolve(
                         self.send(
                           Error(
                             "Erreur lors de la création de la formation",
                           ),
                         ),
                       )
                     }
                   )
                |> catch(_err =>
                     Js.Promise.resolve(
                       self.send(
                         Error("Erreur lors de la création de la formation"),
                       ),
                     )
                   )
                |> ignore
              )
          ),
        )
      },
    didMount: self => getLevel(self),
    render: _self =>
      <div className="card align-middle mx-auto w-50 p-3 text-center col-12">
        <form>
          <div className="card-header">
            (ReasonReact.string({js|Création d'une formation|js}))
          </div>
          <div className="card-body">
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=_self.state.name
                placeholder="Nom de la formation"
                onChange=(
                  event =>
                    _self.send(
                      UpdateNameField(ReactEvent.Form.target(event)##value),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=_self.state.description
                placeholder="Description de la formation"
                onChange=(
                  event =>
                    _self.send(
                      UpdateDescriptionField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <div className="input-group-prepend">
                <span className="input-group-text" id="">
                  (ReasonReact.string("Niveau :"))
                </span>
              </div>
              <select
                className="form-control"
                id="pet-select"
                onChange=(
                  event =>
                    _self.send(
                      UpdateExpertiseField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )>
                <option value="">
                  (ReasonReact.string("Choix du niveau"))
                </option>
                (
                  ReasonReact.array(
                    Array.of_list(
                      List.map(
                        level =>
                          <option value=level.title>
                            (ReasonReact.string(level.title))
                          </option>,
                        _self.state.listLevel,
                      ),
                    ),
                  )
                )
              </select>
            </div>
            <div className="input-group mb-3">
              <div className="input-group-prepend">
                <span className="input-group-text" id="">
                  (ReasonReact.string("Alternance :"))
                </span>
              </div>
              <select
                className="form-control"
                id="pet-select"
                onChange=(event => select_partTime(event, _self))>
                <option value="">
                  (ReasonReact.string("Choix d'une option"))
                </option>
                <option value="true"> (ReasonReact.string("Oui")) </option>
                <option value="false"> (ReasonReact.string("Non")) </option>
              </select>
            </div>
            <div className="input-group mb-3">
              <div className="input-group-prepend">
                <span className="input-group-text" id="">
                  (ReasonReact.string("Url de la photo :"))
                </span>
              </div>
              <input
                className="form-control"
                type_="text"
                placeholder="http://www.img.test/img"
                onChange=(
                  event =>
                    _self.send(
                      UpdateLogoPath(ReactEvent.Form.target(event)##value),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=_self.state.link
                placeholder={js|lien du site de l'école|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateLinkField(ReactEvent.Form.target(event)##value),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=_self.state.duration
                placeholder={js|Durée de la formation|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateDurationField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=_self.state.schoolName
                placeholder={js|Nom de l'école|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateSchoolNameField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=_self.state.schoolDescription
                placeholder={js|Description de l'école|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateSchoolDescriptionField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=_self.state.schoolPostalCode
                placeholder={js|Code postale de la ville de l'école|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateSchoolPostalCodeField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=_self.state.schoolCity
                placeholder={js|Nom de la ville de l'école|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateSchoolCityField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
          </div>
        </form>
        <div className="justify-content-center">
          <button
            className="btn btn-outline-primary"
            onClick=(_ => _self.send(CreateTraining))>
            (ReasonReact.string("Annuler"))
          </button>
          <button
            className="btn btn-outline-primary"
            onClick=(_ => _self.send(CreateTraining))>
            (ReasonReact.string("Envoyer"))
          </button>
        </div>
        <label> (ReasonReact.string(_self.state.name)) </label>
        <label> (ReasonReact.string(_self.state.description)) </label>
        <label>
          (ReasonReact.string(string_of_bool(_self.state.partTime)))
        </label>
        <label> (ReasonReact.string(_self.state.error)) </label>
      </div>,
  };
};