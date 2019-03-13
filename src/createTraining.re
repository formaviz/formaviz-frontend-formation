open SessionUser;

let styleInput = ReactDOMRe.Style.make(~paddingLeft="20px");

let url_dev: string = "http://localhost:8080/";

type state = {
  name: string,
  description: string,
  admLevel: string,
  diplomaLevel: string,
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
  | CreateTraining;

let select_partTime = (event, self) => {
  switch (ReactEvent.Form.target(event)##value) {
  | "true" => self.ReasonReact.send(UpdatePartTimeField(true))
  | "false" => self.send(UpdatePartTimeField(false))
  | _ => self.send(UpdatePartTimeField(false))
  };
};

let uploadImg = e => {
  Js.log(e);
};

let string_of_bool = value => {
  value ? "true" : "false";
};

let handleChange = event => {
  Js.log(ReactEvent.Form.target(event)##value);
};

let component = ReasonReact.reducerComponent("createTraining");

let make = _children => {
  ...component,
  initialState: () => {
    name: "",
    description: "",
    admLevel: "",
    diplomaLevel: "",
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
    | UpdateLogoPath(logoPath) =>
      ReasonReact.UpdateWithSideEffects(state, self => uploadImg(logoPath))
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
    | CreateTraining => ReasonReact.NoUpdate
    },
  render: _self =>
    <div className="card align-middle mx-auto w-50 p-3 text-center col-12">
      <form>
        <div className="card-header">
          {ReasonReact.string({js|Création d'une formation|js})}
        </div>
        <div className="card-body">
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value={_self.state.name}
              placeholder="Nom de la formation"
              onChange={event =>
                _self.send(
                  UpdateNameField(ReactEvent.Form.target(event)##value),
                )
              }
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value={_self.state.description}
              placeholder="Description de la formation"
              onChange={event =>
                _self.send(
                  UpdateDescriptionField(
                    ReactEvent.Form.target(event)##value,
                  ),
                )
              }
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value={_self.state.expertise}
              placeholder="Niveau d'expertise"
              onChange={event =>
                _self.send(
                  UpdateExpertiseField(ReactEvent.Form.target(event)##value),
                )
              }
            />
          </div>
          <div className="input-group mb-3">
            <div className="input-group-prepend">
              <span className="input-group-text" id="">
                {ReasonReact.string("Alternance :")}
              </span>
            </div>
            <select
              className="form-control"
              id="pet-select"
              onChange={event => select_partTime(event, _self)}>
              <option value="">
                {ReasonReact.string("Choix d'une option")}
              </option>
              <option value="true"> {ReasonReact.string("Oui")} </option>
              <option value="false"> {ReasonReact.string("Non")} </option>
            </select>
          </div>
          <div className="input-group mb-3">
            <div className="input-group-prepend">
              <span className="input-group-text" id="">
                {ReasonReact.string("Url de la photo :")}
              </span>
            </div>
            <input
              className="form-control"
              type_="text"
              placeholder="http://www.img.test/img"
              onChange={event =>
                _self.send(
                  UpdateLogoPath(ReactEvent.Form.target(event)##value),
                )
              }
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value={_self.state.link}
              placeholder={js|lien du site de l'école|js}
              onChange={event =>
                _self.send(
                  UpdateLinkField(ReactEvent.Form.target(event)##value),
                )
              }
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value={_self.state.duration}
              placeholder={js|Durée de la formation|js}
              onChange={event =>
                _self.send(
                  UpdateDurationField(ReactEvent.Form.target(event)##value),
                )
              }
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value={_self.state.schoolName}
              placeholder={js|Nom de l'école|js}
              onChange={event =>
                _self.send(
                  UpdateSchoolNameField(
                    ReactEvent.Form.target(event)##value,
                  ),
                )
              }
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value={_self.state.schoolDescription}
              placeholder={js|Description de l'école|js}
              onChange={event =>
                _self.send(
                  UpdateSchoolDescriptionField(
                    ReactEvent.Form.target(event)##value,
                  ),
                )
              }
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value={_self.state.schoolPostalCode}
              placeholder={js|Code postale de la ville de l'école|js}
              onChange={event =>
                _self.send(
                  UpdateSchoolPostalCodeField(
                    ReactEvent.Form.target(event)##value,
                  ),
                )
              }
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value={_self.state.schoolCity}
              placeholder={js|Nom de la ville de l'école|js}
              onChange={event =>
                _self.send(
                  UpdateSchoolCityField(
                    ReactEvent.Form.target(event)##value,
                  ),
                )
              }
            />
          </div>
        </div>
      </form>
      <div className="justify-content-center">
        <button
          className="btn btn-outline-primary"
          onClick={_ => _self.send({CreateTraining})}>
          {ReasonReact.string("Annuler")}
        </button>
        <button
          className="btn btn-outline-primary"
          onClick={_ => _self.send({CreateTraining})}>
          {ReasonReact.string("Envoyer")}
        </button>
      </div>
      <label> {ReasonReact.string(_self.state.name)} </label>
      <label> {ReasonReact.string(_self.state.description)} </label>
      <label>
        {ReasonReact.string(string_of_bool(_self.state.partTime))}
      </label>
      <label> {ReasonReact.string(_self.state.error)} </label>
    </div>,
};